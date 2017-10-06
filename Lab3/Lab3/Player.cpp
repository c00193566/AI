#include "Player.h"

void Player::Initialise()
{
	float x = rand() % 21 + (-10);

	float y = rand() % 21 + (-10);

	Velocity = Vector2f(x, y);

	if (!CharacterTexture.loadFromFile("ASSETS/Player.png"))
	{
		cout << "Unable to load NPC image" << endl;
	}

	CharacterSprite.setTexture(CharacterTexture);

	CharacterSprite.setOrigin(CharacterTexture.getSize().x / 2.0f, CharacterTexture.getSize().y / 2.0f);

	Position = Vector2f(672, 450);

	CharacterSprite.setPosition(Position);
}

void Player::PlayerInput()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		Magnitude += 0.1f;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		Magnitude -= 0.1f;
	}

	if (Magnitude > 5)
	{
		Magnitude = 5;
	}

	if (Magnitude < -5)
	{
		Magnitude = -5;
	}

}

void Player::Update(RenderWindow & Window) {
	PlayerInput();
	Movement();
	Draw(Window);
	Collision();
}