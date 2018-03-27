#include "EnemyAIComponent.h"




EnemyAIComponent::EnemyAIComponent()
{
	velocity = glm::vec3(0, 0, 0);	
}


void EnemyAIComponent::init()
{
	//Give the object an initial route to follow
	targetIndex = 0;
	
	targets.push_back(glm::vec3(50, 0, 0));
	targets.push_back(glm::vec3(0, 0, 50));
	targets.push_back(glm::vec3(0, 0, -50));
	targets.push_back(glm::vec3(-50, 0, 0));

	currentGoalPosition = targets[targetIndex];

	glm::vec2 goal(currentGoalPosition.x, currentGoalPosition.z);

	currentRoute = AIsystem->findPath(glm::vec2(0, 0), goal);
	goalNodeIndex = 0;

	atFinalDestination = false;
}



void EnemyAIComponent::update()
{
	glm::vec3 currPosition = this->getUser()->getPosition();

	
	
	//Recalculate route with nw destination
	if (currentRoute.size() == 0)
	{
		goalNodeIndex = 0;
		targetIndex++;

		if (targetIndex >= targets.size() - 1)
			targetIndex = 0;

		currentGoalPosition = targets[targetIndex];

		glm::vec2 pos(currPosition.x, currPosition.z);
		glm::vec2 goal(currentGoalPosition.x, currentGoalPosition.z);

		currentRoute = AIsystem->findPath(pos, goal);
	}
		




	if (!atFinalDestination)
	{
		//Still travelling to next position
		if (glm::distance(currPosition, currentRoute[goalNodeIndex]) > 5) 
		{
			velocity = glm::normalize(currentRoute[goalNodeIndex] - currPosition);
			velocity = velocity * glm::vec3(0.05, 0, 0.05);
		}
		else
		{
			
			if (glm::distance(currPosition, currentRoute[currentRoute.size()-1]) < 5)
			{
				atFinalDestination = true;
				velocity = glm::vec3(0);
			}
			else//Make next node the target
			{
				goalNodeIndex++;
			}
		
		}
			
	}
	else
	{
		// Decide where the next goal lies
		targetIndex++;

		

		if (targetIndex >= targets.size() - 1)
			targetIndex = 0;

		currentGoalPosition = targets[targetIndex];

		glm::vec2 pos(currPosition.x, currPosition.z);
		glm::vec2 goal(currentGoalPosition.x, currentGoalPosition.z);

		currentRoute = AIsystem->findPath(pos, goal);

		atFinalDestination = false;

		goalNodeIndex = 0;

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