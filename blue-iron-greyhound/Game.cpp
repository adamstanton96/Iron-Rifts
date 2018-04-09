#include "Game.h"



Game::Game(std::vector<GameObject*> scene)
{
	this->scene = scene;
}



void Game::init()
{

}

void Game::update(double dt)
{
	//Update all objects
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if(players[i]->isAlive == true)
		players[i]->update(dt);
		else
		{
			players[i]->setPosition(glm::vec3(-1000));
			players[i]->update(dt);
			//players[i]->isAlive 
		}
		
	}

	for (unsigned int i = 0; i < scene.size(); i++)
	{
		scene[i]->update(dt);
	}


}

void Game::addPlayers(std::vector<GameObject*> players)
{
	this->players = players;
}