#pragma once
#include "Character.h"

struct KinematicMethods {
	void Seek(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Seek(Character* Input, Vector2f Target, CalculationMethods VectorModifiers);
	void Pursuit(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Arrive(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Arrive(Character* Input, Vector2f Target, CalculationMethods VectorModifiers);
	void Flee(Character* Input, Character* Target, CalculationMethods VectorModifiers);
	void Wander(Character* Input, WanderComponents* Target, CalculationMethods VectorModifiers);
	float getOrientation(float CurrentOrientation, Vector2f Velocity, CalculationMethods VectorModifiers);
};