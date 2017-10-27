#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14

using namespace std;
using namespace sf;

struct WanderComponents {
	float LastUpdate = 0.0f;
	float Distance = 150;
	float Radius = 25;
	Vector2f Target = Vector2f(rand() % WIDTH, rand() % HEIGHT);
};

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

enum class MovementBehaviour { Null, Seek, Pursuit, Flee, Arrive, Wander };

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
	void Collision();
};