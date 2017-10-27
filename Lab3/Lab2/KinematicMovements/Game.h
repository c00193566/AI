#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "Player.h"

using namespace sf;
using namespace std;

struct KinematicMethods {
	void Seek(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Seek(Character* Input, Vector2f Target, CalculationMethods VectorModifiers);
	void Pursuit(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Arrive(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Flee(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Wander(Character* Input, WanderComponents* Target, CalculationMethods VectorModifiers);
	float getOrientation(float CurrentOrientation, Vector2f Velocity, CalculationMethods VectorModifiers);
};

class Game {
private:
	Time CurrentTime;
	const Time FPS = seconds(1.0f / 60.0f);
	Clock UpdateClock;

	KinematicMethods MovementTypes;
	CalculationMethods Modifiers;
	WanderComponents* WanderVar;

	Character* NPC_01 =  new Character;
	Character* NPC_02 = new Character;
	Character* NPC_03 = new Character;
	Player* User = new Player;

public:
	Game();
	~Game();
	void Init();
	void Run();
	void EventHandler(Event event);
	void Render();
	void Update();
};