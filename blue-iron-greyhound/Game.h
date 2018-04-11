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
	
	GameObject *getThePlayer() { return this->thePlayer; }
	void setThePlayer(GameObject *thePlayer) { this->thePlayer = thePlayer; }
private:
	double cooldownTimer, respawnTime;
	std::vector<GameObject*> scene;
	std::vector<GameObject*> players;

	GameObject *thePlayer;
};
