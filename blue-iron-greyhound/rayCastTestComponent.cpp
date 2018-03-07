#include "rayCastTestComponent.h"

RayCastTestComponent::RayCastTestComponent(std::string name)
{
	this->name = name;
}

RayCastTestComponent::~RayCastTestComponent()
{
}

void RayCastTestComponent::init()
{
}

void RayCastTestComponent::update()
{
	if (this->input->keyPressed("R"))
	{
		Ray blappo = physics->castRay(this->getUser()->getPosition(), glm::vec3(0.0f, 0.0f, -1.0f), 20.0f);
		std::vector<GameObject*> bleppo = physics->checkRayCollision(blappo);
		GameObject * bloppo = physics->checkClosest(this->getUser(), bleppo);
		if (bloppo != nullptr)
		{
			std::cout << bloppo->getName() << std::endl;
		}
		else
		{
			std::cout << "No Collision Mah Dude" << std::endl;
		}
			
	}
}

void RayCastTestComponent::setInput(InputSystem * newInput)
{
	input = newInput;
}

void RayCastTestComponent::setPhysics(PhysicsSystem * newPhysics)
{
	physics = newPhysics;
}
