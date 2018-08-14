#pragma once
#include "AbstractState.h"
#include "GameObject.h"


class MainMenuState : public AbstractState
{
public:
	MainMenuState(GameObject* menuObject);

	void init();
	void update(double dt, IronRifts* game);

	void Cleanup();
	void Resume();
	void Pause();


private:
	GameObject * menu;

	//std::vector<GameObject*>  subMenus;
};
