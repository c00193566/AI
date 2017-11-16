#include "FormationV.h"

FormationV::FormationV()
{
	DisplayPoints = vector<CircleShape>(5); // Set up size of vector array for circle shapes

	numberOfPositions = 5;

	characters = vector<Character*>(numberOfPositions);

	positions = vector<Vector2f>(numberOfPositions); // Set up size of vector array for positions

	// Setup Positions
	positions.at(0) = Vector2f(200.0f, 200.0f);
	positions.at(1) = Vector2f(150.0f, 250.0f);
	positions.at(2) = Vector2f(250.0f, 250.0f);
	positions.at(3) = Vector2f(100.0f, 300.0f);
	positions.at(4) = Vector2f(300.0f, 300.0f);

	// Setup Anchor
	Anchor = Vector2f(200.0f, 380.0f);
	AnchorVelocity = Vector2f(0.0f, -25.0f);

	DistanceFromAnchor = vector<float>();
	RotationFromAnchor = vector<float>();

	for (int i = 0; i < positions.size(); i++)
	{
		DistanceFromAnchor.push_back(calculations.Distance(Anchor, positions.at(i)));
		RotationFromAnchor.push_back(calculations.Rotation(Anchor, positions.at(i)));

		cout << RotationFromAnchor.at(i) << endl;
	}

	// Setup Display points
	float radius = 5;
	for (int i = 0; i < DisplayPoints.size(); i++)
	{
		if (i == Leader)
		{
			DisplayPoints.at(i).setFillColor(Color::Green);
		}
		else
		{
			DisplayPoints.at(i).setFillColor(Color::Red);
		}

		DisplayPoints.at(i).setRadius(radius);
		DisplayPoints.at(i).setOrigin(radius, radius);
		DisplayPoints.at(i).setPosition(positions.at(i));
	}

	DisplayPoints.at(4).setFillColor(Color::Blue);
}

void FormationV::Draw(RenderWindow & window)
{
	for (int i = 0; i < DisplayPoints.size(); i++)
	{
		window.draw(DisplayPoints.at(i));
	}
}

void FormationV::CalcAverageSpeed()
{
	float average = 0.0f;

	for (int i = 0; i < characters.size(); i++)
	{
		average += characters.at(i)->MaxSpeed;
	}

	average /= characters.size();

	AnchorSpeed = average;

	for (int i = 0; i < characters.size(); i++)
	{
		characters.at(i)->ModifiedSpeed = average;
		characters.at(i)->InFormation = true;
	}
}

void FormationV::Update()
{
	DisplayPoints.at(0).setPosition(positions.at(Leader));

	UpdateAnchor();
	PositionUpdate();

	for (int i = 0; i < characters.size(); i++)
	{
		movements.Seek(characters.at(i), positions.at(i), calculations);
	}

	OffScreen();
}

void FormationV::PositionUpdate()
{
	for (int i = 0; i < characters.size(); i++)
	{
		positions.at(i).x = DistanceFromAnchor.at(i) * cos(RotationFromAnchor.at(i)) + Anchor.x;
		positions.at(i).y = DistanceFromAnchor.at(i) * -sin(RotationFromAnchor.at(i)) + Anchor.y;

		DisplayPoints.at(i).setPosition(positions.at(i));
	}
}

void FormationV::UpdateAnchor()
{
	AnchorVelocity = calculations.Normalize(AnchorVelocity);
	AnchorVelocity *= AnchorSpeed;
	Anchor += AnchorVelocity;
	DisplayPoints.at(4).setPosition(Anchor);
}

bool FormationV::Setup(vector<Character*> npcs)
{
	if (npcs.size() > numberOfPositions)
	{
		return false;
	}
	
	characters = npcs;

	CalcAverageSpeed();

	return true;
}

void FormationV::OffScreen()
{
	if (Anchor.y < 0.0f)
	{
		Anchor.y = HEIGHT;
	}

	for (int i = 0; i < characters.size(); i++)
	{
		if (positions.at(i).y < 0.0f)
		{
			float diff = positions.at(i).y * -1;

			positions.at(i).y = HEIGHT + diff;
		}

		DisplayPoints.at(i).setPosition(positions.at(i));
	}
}