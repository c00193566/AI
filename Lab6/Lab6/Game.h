#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "FormationV.h"

using namespace sf;
using namespace std;

class Game {
private:
	Time CurrentTime;
	const Time FPS = seconds(1.0f / 60.0f);
	Clock UpdateClock;

	FormationV v_formation;
	bool grouped;

	KinematicMethods MovementTypes;
	CalculationMethods Modifiers;
	WanderComponents* WanderVar;

	vector<Character*> npcs;

public:
	Game();
	~Game();
	void Init();
	void Run();
	void EventHandler(Event event);
	void Render();
	void Update();
};