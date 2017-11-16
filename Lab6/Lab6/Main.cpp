#pragma once
#include "Game.h"

int main()
{
	Game* game = new Game;

	game->Init();

	game->Run();

	return 0;
}