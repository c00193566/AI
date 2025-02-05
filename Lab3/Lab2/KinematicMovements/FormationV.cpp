#include "FormationV.h"

FormationV::FormationV()
{
	cunts = vector<CircleShape>(5); // Set up size of vector array for circle shapes

	numberOfPositions = 5;

	characters = vector<Character*>(numberOfPositions);

	positions = vector<Vector2f>(numberOfPositions); // Set up size of vector array for positions

	positions.at(0) = Vector2f(200.0f, 200.0f);
	positions.at(1) = Vector2f(150.0f, 250.0f);
	positions.at(2) = Vector2f(250.0f, 250.0f);
	positions.at(3) = Vector2f(100.0f, 300.0f);
	positions.at(4) = Vector2f(300.0f, 300.0f);

	float radius = 5;

	for (int i = 0; i < cunts.size(); i++)
	{
		if (i == Leader)
		{
			cunts.at(i).setFillColor(Color::Green);
		}
		else
		{
			cunts.at(i).setFillColor(Color::Red);
		}

		cunts.at(i).setRadius(radius);
		cunts.at(i).setOrigin(radius, radius);
		cunts.at(i).setPosition(positions.at(i));
	}

}

void FormationV::Draw(RenderWindow & window)
{
	for (int i = 0; i < cunts.size(); i++)
	{
		window.draw(cunts.at(i));
	}
}

void FormationV::Update()
{
	positions.at(Leader) = characters.at(Leader)->CharacterSprite.getPosition();

	cunts.at(0).setPosition(positions.at(Leader));

	PositionUpdate();

	for (int i = 0; i < numberOfPositions; i++)
	{
		if (i != Leader)
		{
			movements.Arrive(characters.at(i), positions.at(i), calculations);
		}
	}
}

void FormationV::PositionUpdate()
{
	positions.at(1) = Vector2f(positions.at(Leader).x - 50, positions.at(Leader).y + 50);
	cunts.at(1).setPosition(positions.at(1));
}

bool FormationV::Setup(vector<Character*> npcs)
{
	if (npcs.size() > numberOfPositions)
	{
		return false;
	}
	
	characters = npcs;

	return true;
}

bool FormationV::Setup(Player* user, vector<Character*> npcs)
{
	if (npcs.size() > numberOfPositions - 1)
	{
		return false;
	}

	for (int i = 0; i < characters.size(); i++)
	{
		if (i == Leader)
		{
			characters.at(i) = user;
		}
		else
		{
			characters.at(i) = npcs.at(i - 1);
			characters.at(i)->Behaviour = MovementBehaviour::Arrive;
		}
	}

	return true;
}