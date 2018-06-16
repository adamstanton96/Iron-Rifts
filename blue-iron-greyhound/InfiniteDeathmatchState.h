#pragma once
#include "AbstractState.h"

/*=============================================================================
* InfiniteDeathmatchState.h
* Author: Adam Stanton (B00266256) & Chloe Madden (B00286864)
* Defines each update of our game loop
=============================================================================*/

#pragma once
#include <vector>
#include "System.h"
#include "GameObject.h"

class InfiniteDeathmatchState : public AbstractState
{
public:
	InfiniteDeathmatchState(std::vector<GameObject*> scene, std::vector<GameObject*> players);
	~InfiniteDeathmatchState() {}


	void init();
	void update(double dt);
	void addPlayers(std::vector<GameObject*> players);

private:
	double cooldownTimer, respawnTime;
	std::vector<GameObject*> scene;
	std::vector<GameObject*> players;

	void sortLeaderboard();

	int GameWinningScore;
};
