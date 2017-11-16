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
		if (i == 3)
		{
			npcs.at(i)->Init(Vector2f(rand() % WIDTH, rand() % HEIGHT), "Ship_04");
		}
		else if (i == 2)
		{
			npcs.at(i)->Init(Vector2f(rand() % WIDTH, rand() % HEIGHT), "Ship_03");
		}
		else if (i == 1)
		{
			npcs.at(i)->Init(Vector2f(rand() % WIDTH, rand() % HEIGHT), "Ship_02");
		}
		else if (i == 0)
		{
			npcs.at(i)->Init(Vector2f(rand() % WIDTH, rand() % HEIGHT), "Ship_01");
		}
		npcs.at(i)->Behaviour = MovementBehaviour::Seek;
		npcs.at(i)->MaxSpeed = rand() % 6 + 1;
	}

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
				if (!v_formation.Setup(npcs))
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

	MainWindow.display();
}

void Game::Update()
{
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

float CalculationMethods::Distance(Vector2f a, Vector2f b)
{
	float h;

	h = sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));

	return h;
}

float CalculationMethods::Rotation(Vector2f a, Vector2f b)
{
	float rotation = 0.0f;

	Vector2f diff = a - b;

	rotation = atan2f(diff.y, diff.x);

	return rotation;
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