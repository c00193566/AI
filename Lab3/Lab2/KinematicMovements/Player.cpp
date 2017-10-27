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

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		Attributes.Orientation += 1.0f;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
 		Attributes.Orientation -= 1.0f;
	}

	CharacterSprite.setRotation(Attributes.Orientation);

	if (MaxSpeed > 5)
	{
		MaxSpeed = 5;
	}

	if (MaxSpeed < 0)
	{
		MaxSpeed = 0;
	}

}

void Player::Update() {
	PlayerInput();
	Movement();
	SetVelocity();
	Collision();
}

void Player::SetVelocity()
{
	Attributes.Velocity = Vector2f(sin((Attributes.Orientation / 180 * PI)), -cos((Attributes.Orientation / 180 * PI)));
	cout << CharacterSprite.getRotation() << endl;
	cout << "DIR (" << Attributes.Velocity.x << " , " << Attributes.Velocity.y << ")" << endl;
	Attributes.Velocity = Modifiers.Normalize(Attributes.Velocity);
	Attributes.Velocity *= MaxSpeed;
}