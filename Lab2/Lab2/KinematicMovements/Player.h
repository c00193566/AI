#pragma once
#include "Character.h"

class Player : public Character
{
public:
	void PlayerInput();
	virtual void Update(RenderWindow & Window);
};