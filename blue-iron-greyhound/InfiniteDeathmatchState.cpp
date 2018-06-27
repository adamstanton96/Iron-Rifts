
#include "InfiniteDeathmatchState.h"
#include "MechanicsComponent.h"


InfiniteDeathmatchState::InfiniteDeathmatchState(std::vector<GameObject*> scene, std::vector<GameObject*> players)
{
	this->scene = scene;
	this->players = players;
	this->respawnTime = 20;
	this->cooldownTimer = 21;

	this->GameWinningScore = 10;

	timer = 0;
	timeThreshold = 0.2;
}



void InfiniteDeathmatchState::init()
{
	inputs.init();		// Not good because every state will call init on the Input object and its not needed.
}

void InfiniteDeathmatchState::update(double dt, IronRifts* game)
{

	timer += dt;

	if (timer >= timeThreshold)
	{
		if (this->inputs.keyPressed("P"))
		{
			std::cout << "Game Paused" << std::endl;
			game->pushState(game->pauseState);

			timer = 0;
		}
	}


	cooldownTimer += dt;

	//Update character objects
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i]->isAlive == true)
			players[i]->update(dt);
		else
		{
			players[i]->setPosition(glm::vec3(-10000));
			if (!players[i]->getComponent<MechanicsComponent>()->getAwaitingRespawn())
			{
				players[i]->update(dt);
				players[i]->getComponent<MechanicsComponent>()->setAwaitingRespawn(true);
			}
		}


		//Flag the winner if there is one
		if (players[0]->getComponent<MechanicsComponent>()->score >= GameWinningScore)
		{
			std::cout << players[0]->getName() << " is the winner!!!" << std::endl;
		}





	}

	//Update scene objects
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

	//std::cout << "Leaderbaord" << std::endl;
	//Print it...
	for (int i = 0; i < players.size(); i++)
	{
		//	std::cout << i << ") " << players[i]->getName() << " - Score: " << players[i]->getComponent<MechanicsComponent>()->score << std::endl;
	}


}

void InfiniteDeathmatchState::addPlayers(std::vector<GameObject*> players)
{
	this->players = players;
}

void InfiniteDeathmatchState::sortLeaderboard()
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



InfiniteDeathmatchState::~InfiniteDeathmatchState()
{
	for (int i = 0; i < players.size() - 1; i++)
		delete players[i];

	for (int i = 0; i < scene.size() - 1; i++)
		delete scene[i];

	
}

void InfiniteDeathmatchState::Cleanup()
{
	delete this;
}


void InfiniteDeathmatchState::Resume()
{
	isPaused = false;
}


void InfiniteDeathmatchState::Pause()
{
	isPaused = true;
}
