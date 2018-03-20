#include "EnemyAIComponent.h"


EnemyAIComponent::EnemyAIComponent()
{
	velocity = glm::vec3(0, 0, 0);
	newDestination = true;
	
}


void EnemyAIComponent::init()
{
	currentRoute = AIsystem->findPath(glm::vec2(0, 0), glm::vec2(0, 10));
}


void EnemyAIComponent::update()
{
	glm::vec3 currPosition = this->getUser()->getPosition();

	
		//// If at the destination of our current path
		//if (currentRoute[currentRoute.size() - 1] == glm::vec2(currPosition.x, currPosition.z))
		//{
		//	newDestination = true;
		//	currentRoute = AIsystem->findPath(glm::vec2(currPosition.x, currPosition.z), glm::vec2(0, 10));
		//}
		//else
		//{

		}
	
	

	

	this->getUser()->setPosition(currPosition + velocity);


	
}


void EnemyAIComponent::setCollisionSystem(PhysicsSystem* collisionSystem)
{
	collisionSys = collisionSystem;
}

void EnemyAIComponent::setAIsystem(AISystem* ai)
{
	AIsystem = ai;
}