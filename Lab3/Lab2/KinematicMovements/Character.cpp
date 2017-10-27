#include "Character.h"

Character::Character() {}

Character::~Character() {}

void Character::Init(Vector2f SetUpPosition, string LoadTexture)
{
	string path = "Assets/" + LoadTexture + ".png";

	if (!(CharacterTexture.loadFromFile(path)))
	{
		cout << "Could not load " << LoadTexture << endl;
	}

	CharacterSprite.setTexture(CharacterTexture);

	CharacterSprite.setOrigin(CharacterTexture.getSize().x / 2, CharacterTexture.getSize().y / 2);

	Attributes.Position = SetUpPosition;

	CharacterSprite.setPosition(Attributes.Position);

	Attributes.Velocity = Vector2f(0.0f, 0.0f);
}

void Character::Draw(RenderWindow & MainWindow)
{
	MainWindow.draw(CharacterSprite);
}

void Character::Update()
{
	Movement();
	Collision();
}

void Character::Movement()
{
	Attributes.Position += Attributes.Velocity;

	CharacterSprite.setPosition(Attributes.Position);
}

void Character::Collision()
{
	// Top of screen
	if (CharacterSprite.getPosition().y <= 0)
	{
		Attributes.Position.y = 868.0f;
	}
	// Bottom of screen
	else if (CharacterSprite.getPosition().y >= 900)
	{
		Attributes.Position.y = 32.0f;
	}

	// Right of Screen
	if (CharacterSprite.getPosition().x >= 1600)
	{
		Attributes.Position.x = 32.0f;
	}
	// Left of Screen
	else if (CharacterSprite.getPosition().x <= 0)
	{
		Attributes.Position.x = 1568.0f;
	}

	CharacterSprite.setPosition(Attributes.Position);
}