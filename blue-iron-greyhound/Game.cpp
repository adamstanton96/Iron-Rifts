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
	players[0]->getComponent<MechanicsComponent>()->score = 0;
	players[1]->getComponent<MechanicsComponent>()->score = 12;
	players[2]->getComponent<MechanicsComponent>()->score = 44;
	players[3]->getComponent<MechanicsComponent>()->score = 2;
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
			//std::cout << players[i]->getName() << " is the winner!!!";
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

	sortLeaderboard();

	for (int i = 0; i < players.size(); i++)
	{
		std::cout << players[i]->getName() << " - Score: " << players[i]->getComponent<MechanicsComponent>()->score << std::endl;
	}


}

void Game::addPlayers(std::vector<GameObject*> players)
{
	this->players = players;
}

void Game::sortLeaderboard()
{
	//perform a sort on the leaderboard vector based on their mechanicscomponent score value:
	bool swapped = true;
	int j = 0;
	GameObject* tmp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < players.size() - j; i++) {
			if (players[i]->getComponent<MechanicsComponent>()->score < players[i + 1]->getComponent<MechanicsComponent>()->score)
			{
				tmp = players[i];
				players[i] = players[i + 1];
				players[i + 1] = tmp;
				swapped = true;
			}
		}
	}
}
