#include "InGameMenuState.h"

InGameMenuState::InGameMenuState(GameObject* menuObject)
{
	menu = menuObject;
	timer = 0;
	timeThreshold = 0.2;
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
	timer += dt;

	if (timer >= timeThreshold)
	{
		if (this->inputs.keyPressed("P"))
		{
			std::cout << "Game Un-Paused" << std::endl;
			game->popState();


			timer = 0;
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