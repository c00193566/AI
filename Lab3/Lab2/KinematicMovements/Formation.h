#pragma once
#include "KinematicMethods.h"
#include "Player.h"

class Formation
{
public:

	int numberOfPositions;
	int availablePositions;

	const int Leader = 0;

	KinematicMethods movements;
	CalculationMethods calculations;

	vector<Character*> characters;
	vector<Vector2f> positions;

	virtual void Update() = 0;
};