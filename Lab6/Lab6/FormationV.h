#pragma once
#include "Formation.h"

class FormationV : public Formation
{
private:
	vector<CircleShape> DisplayPoints;

	// Setup anchor
	Vector2f Anchor;
	float AnchorSpeed;
	Vector2f AnchorVelocity;

	// Setup Rotations from anchor
	vector<float> RotationFromAnchor;

	// Setup Distance from anchor
	vector<float> DistanceFromAnchor;

public:
	FormationV();
	~FormationV() {};

	bool Setup(vector<Character*>);
	void Update();
	void PositionUpdate();
	void UpdateAnchor();
	void Draw(RenderWindow& window);
	void CalcAverageSpeed();
	void OffScreen();
};