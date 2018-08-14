#include "InGameMenuState.h"

InGameMenuState::InGameMenuState(GameObject* menuObject)
{
	menu = menuObject;
	inputTimer = 0;
	inputTimerThreshold = 0.2;
}


InGameMenuState::~InGameMenuState()
{

}


void InGameMenuState::init()
{
	this->inputs.init();
	menu->init();
}


void InGameMenuState::update(double dt, IronRifts* game)
{
	inputTimer += dt;

	if (inputTimer >= inputTimerThreshold)
	{
		if (this->inputs.keyPressed("P"))
		{
			std::cout << "Game Un-Paused" << std::endl;
			game->popState();


			inputTimer = 0;
		}


	
	}
	


	menu->update(dt);
}













void InGameMenuState::Cleanup()
{

}


void InGameMenuState::Resume()
{

}


void InGameMenuState::Pause()
{

}