#include "EnemyAIComponent.h"




EnemyAIComponent::EnemyAIComponent()
{
	velocity = glm::vec3(0, 0, 0);	
}


void EnemyAIComponent::init()
{
	//Give the object an initial route to follow
	
	targets.push_back(glm::vec3(100, 0, 0));
	targets.push_back(glm::vec3(-100, 0, 0));
	targets.push_back(glm::vec3(0, 0, 100));
	targets.push_back(glm::vec3(0, 0, -100));

	currentGoalPosition = targets[0];

	currentRoute = AIsystem->findPath(glm::vec2(0, 0), currentGoalPosition);
	goalNodeIndex = 0;

	atFinalDestination = false;
}



void EnemyAIComponent::update()
{
	glm::vec3 currPosition = this->getUser()->getPosition();

	float gradient;

	if (currentRoute.size() == 0)
	{
		goalNodeIndex++;
		currentRoute = AIsystem->findPath(glm::vec2(0, 0), currentGoalPosition);
	}
		

	//Reset target if needed
	if (goalNodeIndex == targets.size() - 1)
	goalNodeIndex = 0;


	if (!atFinalDestination)
	{
		//Still travelling to next position
		if (glm::distance(currPosition, currentRoute[goalNodeIndex]) > 10) 
		{
			velocity = (currPosition - currentRoute[goalNodeIndex]);
			velocity = velocity * glm::vec3(0.005, 0.005, 0.005);
		}
		else
		{
			//at final destination
			if (glm::distance(currPosition, currentRoute[currentRoute.size()-1]) < 10)
			{
				atFinalDestination = true;
				velocity = glm::vec3(0);
			}
			else//Make next node the target
			{
				goalNodeIndex++;
			}
			currentGoalPosition = currentRoute[goalNodeIndex];
		}
			
	}
	else
	{
		//decide where the next goal lies
		currentGoalPosition = targets[0];
		currentRoute = AIsystem->findPath(glm::vec2(0, 0), currentGoalPosition);
	
	}
		
	
	

	
	//update player movement
	this->getUser()->setPosition(currPosition + velocity);


	
}


void EnemyAIComponent::moveTowards(glm::vec2 goal)
{

}



void EnemyAIComponent::setAIsystem(AISystem* ai)
{
	AIsystem = ai;
}