#include "MainMenuState.h"


MainMenuState::MainMenuState(GameObject* menuObject)
{
	menu = menuObject;
	inputTimer = 0;
	inputTimerThreshold = 0.2;
}

void MainMenuState::init()
{
	this->inputs.init();
	menu->init();
}


void MainMenuState::update(double dt, IronRifts* game)
{
	inputTimer += dt;

	if (inputTimer >= inputTimerThreshold)
	{
		if (this->inputs.keyPressed("M"))
		{
			std::cout << "Game Begun" << std::endl;
			game->pushState(game->playState);

			inputTimer = 0;
		}



	}



	menu->update(dt);
}


void MainMenuState::Cleanup()
{

}


void MainMenuState::Resume()
{

}


void MainMenuState::Pause()
{

}
