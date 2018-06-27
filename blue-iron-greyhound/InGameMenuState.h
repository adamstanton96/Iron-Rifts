#pragma once
#include "GameObject.h"
#include <vector>
#include "AbstractState.h"

class InGameMenuState : public AbstractState
{
public:
	InGameMenuState(GameObject* menuObject);
	~InGameMenuState();

	 void init();
	 void update(double dt, IronRifts* game);

	 void Cleanup();
	 void Resume();
	 void Pause();


private:
	GameObject * menu;

	std::vector<GameObject*>  subMenus;
};