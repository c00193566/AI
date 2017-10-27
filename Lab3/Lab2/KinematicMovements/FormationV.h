#pragma once
#include "Formation.h"

class FormationV : public Formation
{
private:
	vector<CircleShape> cunts;

public:
	FormationV();
	~FormationV() {};

	bool Setup(vector<Character*>);
	bool Setup(Player*, vector<Character*>);
	void Update();
	void Draw(RenderWindow& window);
};