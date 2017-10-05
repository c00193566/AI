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
}

void Character::Movement()
{
	Attributes.Position += Attributes.Velocity;

	CharacterSprite.setPosition(Attributes.Position);
}