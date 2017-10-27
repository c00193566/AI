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

	npcs = vector<Character*>(4);

	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i) = new Character;
		npcs.at(i)->Init(Vector2f(rand() % WIDTH, rand() % HEIGHT), "Ship_01");
		npcs.at(i)->Behaviour = MovementBehaviour::Seek;
		npcs.at(i)->MaxSpeed = rand() % 6 + 1;
	}

	User->Init(Vector2f(200, 200), "Ship_03");
	User->Behaviour = MovementBehaviour::Null;
	User->CharacterSprite.setRotation(User->Attributes.Orientation);
	User->MaxSpeed = 0.0f;

	grouped = false;
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

	if (event.type == Event::KeyPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			if (!grouped)
			{
				if (!v_formation.Setup(User, npcs))
				{
					cout << "Too many characters" << endl;
				}
				else
				{
					cout << "Formation set" << endl;
					grouped = true;
				}
			}
		}
	}
}

void Game::Render() {
	MainWindow.clear(Color::White);

	//testing
	v_formation.Draw(MainWindow);

	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->Draw(MainWindow);
	}

	User->Draw(MainWindow);

	MainWindow.display();
}

void Game::Update()
{
	User->Update();

	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->Update();
	}


	if (grouped)
	{
		v_formation.Update();
	}

	Modifiers.RandomClamp();
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