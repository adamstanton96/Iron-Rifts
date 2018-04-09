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
		players[i]->update(dt);
		
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