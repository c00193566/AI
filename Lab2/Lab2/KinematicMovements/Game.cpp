#include "Game.h"

RenderWindow MainWindow(VideoMode(WIDTH, HEIGHT), "Kinematic Movements");


Game::Game() {
	
}

Game::~Game()
{

}

void Game::Init()
{
	CurrentTime = Time::Zero;

	WanderVar = new WanderComponents;

	UpdateClock.restart();

	srand(time(NULL));

	// Set up NPC
	NPC_01->Init(Vector2f((MainWindow.getSize().x / 2) - 128, MainWindow.getSize().y / 2), "Ship_01");
	NPC_01->Behaviour = MovementBehaviour::Seek;
	NPC_01->MaxSpeed = 1.5f;

	NPC_02->Init(Vector2f((MainWindow.getSize().x / 2) + 128, MainWindow.getSize().y / 2), "Ship_02");
	NPC_02->Behaviour = MovementBehaviour::Wander;
	NPC_02->MaxSpeed = 2.0f;

}

void Game::Run()
{
	while (MainWindow.isOpen())
	{
		Event event;

		while (MainWindow.pollEvent(event))
		{
			EventHandler(event);
		}

		CurrentTime += UpdateClock.restart();

		if (CurrentTime > FPS)
		{

			Render();
			Update();

			CurrentTime = Time::Zero;
		}
	}
}

void Game::EventHandler(Event event)
{
	if (event.type == Event::Closed)
	{
		MainWindow.close();
	}
}

void Game::Render() {
	MainWindow.clear(Color::Black);

	NPC_01->Draw(MainWindow);
	NPC_02->Draw(MainWindow);

	MainWindow.display();
}

void Game::Update()
{
	NPC_01->Update();
	NPC_02->Update();

	Modifiers.RandomClamp();

	// Update for NPC_01
	if (NPC_01->Behaviour == MovementBehaviour::Seek)
	{
		MovementTypes.Seek(NPC_01, NPC_02, Modifiers);
	}
	else if (NPC_01->Behaviour == MovementBehaviour::Arrive)
	{
		MovementTypes.Arrive(NPC_01, NPC_02, Modifiers);
	}

	// Update for NPC_02
	if (NPC_02->Behaviour == MovementBehaviour::Seek)
	{
		MovementTypes.Seek(NPC_02, NPC_01, Modifiers);
	}
	else if (NPC_02->Behaviour == MovementBehaviour::Arrive)
	{
		MovementTypes.Arrive(NPC_02, NPC_01, Modifiers);
	}
	else if (NPC_02->Behaviour == MovementBehaviour::Flee)
	{
		MovementTypes.Flee(NPC_02, NPC_01, Modifiers);
	}
	else if (NPC_02->Behaviour == MovementBehaviour::Wander)
	{
		MovementTypes.Wander(NPC_02, WanderVar, Modifiers);
	}
}

float KinematicMethods::getOrientation(float CurrentOrientation, Vector2f Velocity, CalculationMethods VectorModifiers)
{
	float rotation = CurrentOrientation;

	if (VectorModifiers.Length(Velocity) > 0)
	{
		rotation = atan2f(Velocity.x, -Velocity.y);

		rotation = VectorModifiers.RadsToDegs(rotation);
	}

	return rotation;
}

void KinematicMethods::Seek(Character* Input, Character* Target, CalculationMethods VectorModifiers)
{
	Input->Attributes.Velocity = Target->Attributes.Position - Input->Attributes.Position;

	if (VectorModifiers.Length(Input->Attributes.Velocity) < Target->Radius)
	{
		Input->Behaviour = MovementBehaviour::Arrive;
	}
	
	Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

	Input->Attributes.Velocity *= Input->MaxSpeed;

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Seek(Character* Input, Vector2f Target, CalculationMethods VectorModifiers)
{
	Input->Attributes.Velocity = Target - Input->Attributes.Position;

	Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

	Input->Attributes.Velocity *= Input->MaxSpeed;

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Flee(Character* Input, Character* Target, CalculationMethods VectorModifiers)
{
	Input->Attributes.Velocity = Input->Attributes.Position - Target->Attributes.Position;

	Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

	Input->Attributes.Velocity *= Input->MaxSpeed;

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Arrive(Character* Input, Character* Target, CalculationMethods VectorModifiers)
{
	float TimeToTarget = 0.01f;

	Input->Attributes.Velocity = Target->Attributes.Position - Input->Attributes.Position;

	if (VectorModifiers.Length(Input->Attributes.Velocity) > Target->Radius)
	{
		Input->Behaviour = MovementBehaviour::Seek;
	}

	Input->Attributes.Velocity *= TimeToTarget;

	if (VectorModifiers.Length(Input->Attributes.Velocity) > Input->MaxSpeed)
	{
		Input->Attributes.Velocity = VectorModifiers.Normalize(Input->Attributes.Velocity);

		Input->Attributes.Velocity *= Input->MaxSpeed;
	}

	Input->Attributes.Orientation = getOrientation(Input->Attributes.Orientation, Input->Attributes.Velocity, VectorModifiers);

	Input->CharacterSprite.setRotation(Input->Attributes.Orientation);
}

void KinematicMethods::Wander(Character* Input, WanderComponents* Target, CalculationMethods Calc)
{
	Target->LastUpdate += 1.0f / 60.0f;

	if (Target->LastUpdate >= 0.35f)
	{
		Target->LastUpdate = 0.0f;
	}

	if (Target->LastUpdate == 0.0f || Input->Attributes.Position == Target->Target)
	{
		Vector2f Dir = Calc.Normalize(Input->Attributes.Velocity);
		Vector2f Point = Dir * Target->Distance;
		Point += Input->Attributes.Position;
		
		float angle = (static_cast<float>(rand() / (RAND_MAX / 361.0f))) * PI / 180;
		angle *= Calc.RandomClamp();

		float x = Target->Radius * sin(angle) + Point.x;
		float y = Target->Radius * cos(angle) + Point.y;

		Point = Vector2f(x, y);

		Target->Target = Point;
	}

	Seek(Input, Target->Target, Calc);
}

float CalculationMethods::Length(Vector2f Vector)
{
	float VectorLength = sqrtf(pow(Vector.x, 2) + pow(Vector.y, 2));
	
	return VectorLength;
}

Vector2f CalculationMethods::Normalize(Vector2f Vector)
{
	float length = Length(Vector);

	if (length > 0)
	{
		Vector2f VectorNormal = Vector2f(Vector.x / length, Vector.y / length);
		return VectorNormal;
	}
	else
	{
		return Vector2f(0, 0);
	}
}

float CalculationMethods::RadsToDegs(float Rads)
{
	float degs = Rads * 180 / 3.14;

	return degs;
}

float CalculationMethods::RandomClamp()
{
	float ClampValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 2);

	ClampValue -= 1.0f;

	return ClampValue;
}