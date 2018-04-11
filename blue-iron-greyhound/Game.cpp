#include "Game.h"
#include "MechanicsComponent.h"

Game::Game(std::vector<GameObject*> scene)
{
	this->scene = scene;
	this->respawnTime = 45;
	this->cooldownTimer = 46;
}



void Game::init()
{

}

void Game::update(double dt)
{
	cooldownTimer += dt;

	//Update all objects
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if(players[i]->isAlive == true)
			players[i]->update(dt);
		else
		{
			players[i]->setPosition(glm::vec3(-1000));
			if (!players[i]->getComponent<MechanicsComponent>()->getAwaitingRespawn())
			{
				players[i]->update(dt);
				players[i]->getComponent<MechanicsComponent>()->setAwaitingRespawn(true);
			}
		}


		if (players[i]->getComponent<MechanicsComponent>()->score >= 5)
		{
			std::cout << players[i]->getName() << " is the winner!!!";
		}




		
	}

	for (unsigned int i = 0; i < scene.size(); i++)
	{
		scene[i]->update(dt);
	}

	if (cooldownTimer > respawnTime)
	{
		for (unsigned int i = 0; i < players.size(); i++)
		{
			if (!players[i]->isAlive)
			{
				players[i]->setPosition(glm::vec3(0));
				players[i]->isAlive = true;
				players[i]->getComponent<MechanicsComponent>()->init();
				players[i]->getComponent<MechanicsComponent>()->setAwaitingRespawn(false);
			}

		}

		cooldownTimer = 0;
	}


	//Sort the playerlist in order of score:






}

void Game::addPlayers(std::vector<GameObject*> players)
{
	this->players = players;
}