#pragma once
#include <vector>
#include "System.h"
#include "GameObject.h"


class Game : public System
{
public:
	Game(std::vector<GameObject*> scene);
	~Game(){}


	void init();
	void update(double dt);
	void addPlayers(std::vector<GameObject*> players);
	
private:
	double cooldownTimer, respawnTime;
	std::vector<GameObject*> scene;
	std::vector<GameObject*> players;

	void sortLeaderboard();
};
