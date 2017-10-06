#include "Player.h"

void Player::PlayerInput()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		MaxSpeed += 0.1f;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		MaxSpeed -= 0.1f;
	}

	if (MaxSpeed > 5)
	{
		MaxSpeed = 5;
	}

	if (MaxSpeed < -5)
	{
		MaxSpeed = -5;
	}

}

void Player::Update(RenderWindow & Window) {
	PlayerInput();
	Movement();
	Draw(Window);
}