#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

struct CalculationMethods {
	float Length(Vector2f Vector);
	Vector2f Normalize(Vector2f Vector);
	float RadsToDegs(float Radians);
	float RandomClamp();
};

struct CharacterAttributes {
	Vector2f Position;
	Vector2f Velocity = Vector2f(0.0f, 0.0f);
	float Orientation = 0;
	float Rotation = 0;
};

enum class MovementBehaviour { Seek, Flee, Arrive, Wander };

class Character {
public:
	Texture CharacterTexture;
	Sprite CharacterSprite;
	CharacterAttributes Attributes;
	CalculationMethods Modifiers;

	MovementBehaviour Behaviour;

	float MaxSpeed = 1.0f;

	const float Radius = 96.0f;


	Character();
	~Character();
	void Init(Vector2f SetUpPosition, string LoadTexture);
	void Draw(RenderWindow & MainWindow);
	void Update();
	void Movement();
};