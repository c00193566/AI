#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 



#include "SFML\Graphics.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"

using namespace sf;
using namespace std;

int main()
{
	// Create Render Window
	RenderWindow window(VideoMode(1600, 900, 32), "Testing Text Input and Display");

	// NPC
	Character NPC;
	NPC.Initialise();

	Player User;
	User.Initialise();

	// Shit for game loop
	const Time FPS = seconds(1.0f / 60.0f);
	Time CurrentTime = Time::Zero;
	Clock UpdateClock;

	UpdateClock.restart();

	while (window.isOpen())
	{
		Event event;
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		CurrentTime += UpdateClock.restart();

		if (CurrentTime >= FPS)
		{
			window.clear();

			NPC.Update(window);
			User.Update(window);

			window.display();

			CurrentTime = Time::Zero;
		}
	}

	return 0;
}