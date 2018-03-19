#include "rayCastTestComponent.h"
#define DEG_TO_RADIAN 0.017453293

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

		glm::vec3 forward(0, 0, 1);
		glm::vec3 up(0, 1, 0);

		float theta = this->getUser()->getRotationDegrees() * DEG_TO_RADIAN;


		double cos_thetaf = cos(theta);
		glm::vec3 cos_theta(cos(theta));
		glm::vec3 sin_theta(sin(theta));

		glm::dvec3 rotated = (forward * cos_theta) + (glm::cross(up, forward) * sin_theta) + (up * glm::dot(up, forward)) * glm::vec3((1 - cos_thetaf));



		std::cout << rotated.x <<", " << rotated.y<< ", " << rotated.z << std::endl;


		Ray blappo = physics->castRay(this->getUser()->getPosition(), rotated, 100.0f);
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
