#include "Character.h"

void Character::Movement()
{
	Position += Velocity * Magnitude;

	CharacterSprite.setPosition(Position);
}

void Character::Update(RenderWindow & Window) 
{
	Movement();
	Draw(Window);
	Collision();
}

void Character::Draw(RenderWindow & Window)
{
	Window.draw(CharacterSprite);
}

void Character::Collision()
{
	// Top of screen
	if (CharacterSprite.getPosition().y <= 0)
	{
		Position.y = 868.0f;
	}
	// Bottom of screen
	else if (CharacterSprite.getPosition().y >= 900)
	{
		Position.y = 32.0f;
	}

	// Right of Screen
	if (CharacterSprite.getPosition().x >= 1600)
	{
		Position.x = 32.0f;
	}
	// Left of Screen
	else if (CharacterSprite.getPosition().x <= 0)
	{
		Position.x = 1568.0f;
	}

	CharacterSprite.setPosition(Position);
}

void Character::Initialise()
{
	srand(time(NULL));
	float x = rand() % 21 + (-10);
	cout << x << endl;

	float y = rand() % 21 + (-10);
	cout << y << endl;

	Velocity = Vector2f(x, y);

	if (!CharacterTexture.loadFromFile("ASSETS/NPC.png"))
	{
		cout << "Unable to load NPC image" << endl;
	}

	CharacterSprite.setTexture(CharacterTexture);

	CharacterSprite.setOrigin(CharacterTexture.getSize().x / 2.0f, CharacterTexture.getSize().y / 2.0f);

	Position = Vector2f(928, 450);

	CharacterSprite.setPosition(Position);

}