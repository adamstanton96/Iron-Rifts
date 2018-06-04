#pragma once
#include "Component.h"
//This class will hold and render all the HUD items

class PlayerHUd : public Component
{
public:
	PlayerHUd(){}

	~PlayerHUd(){};

	void init();

	void update(double dt);

private:

};
