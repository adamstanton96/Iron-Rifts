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

	//faceDestination(glm::vec2(0, 0), currentRoute[goalNodeIndex]);

	atFinalDestination = false;
}

void EnemyAIComponent::faceDestination(glm::vec3 pos, glm::vec3 dest)
{
	//Calculates angle and set player rotation
	//Really just an up vector 
	glm::vec3 playerVec(0, 1,0);

	//Mouse position and an x, y representing the center of the screen
	glm::vec3 facingVector = dest - pos;

	float angleInDegrees_ = atan2(facingVector.y, facingVector.x) - atan2(playerVec.y, playerVec.x);
	angleInDegrees_ = glm::degrees(angleInDegrees_);

	//Set players rotation based on where the mouse is!
	this->user->setRotationDegrees(angleInDegrees_+90);
}

void EnemyAIComponent::update()
{
	glm::vec3 currPosition = this->getUser()->getPosition();

	//Stops vector subscript out of range errors
	if (goalNodeIndex > currentRoute.size() - 1)
		goalNodeIndex = 0;


	faceDestination(currPosition, currentRoute[goalNodeIndex]);
	
	
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
		
	


	//Not at last node in the current path
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

		

		if (targetIndex > targets.size() - 1)
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