#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

class Character
{
public:
	Sprite CharacterSprite;
	Texture CharacterTexture;
	Vector2f Velocity = Vector2f(0.0f, 0.0f);
	Vector2f Position = Vector2f(0.0f, 0.0f);
	float Magnitude = 1.0f;
	virtual void Initialise();
	void Movement();
	void Collision();
	virtual void Update(RenderWindow & Window);
	virtual void Draw(RenderWindow & Window);
};