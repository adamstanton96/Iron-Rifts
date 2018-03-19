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


		//Calculate the rays direction
		glm::vec3 forward(0, 0, -1);
		glm::vec3 up(0, 1, 0);

		double theta = (this->getUser()->getRotationDegrees() * DEG_TO_RADIAN) - 0.16;

		double cos_thetaf = cos(theta);
		glm::vec3 cos_theta(cos(theta));
		glm::vec3 sin_theta(sin(theta));

		glm::dvec3 rotated = (forward * cos_theta) + (glm::cross(up, forward) * sin_theta) + (up * glm::dot(up, forward)) * glm::vec3((1 - cos_thetaf));
		rotated = glm::vec3(rotated.x, rotated.y, -rotated.z);

		//cout << rotated.x << ", " << rotated.y << ", "<< rotated.z << endl;
		//Find the two points defining our ray 
		Ray blappo = physics->castRay(this->getUser()->getPosition(), rotated, 50.0f);

		//Get all objects in the pathh of the ray
		std::vector<GameObject*> bleppo = physics->checkRayCollision(blappo);

		//Find out which collided object is closest to the player
		GameObject* obj = nullptr;

		if (bleppo.size() != 0)
		obj = physics->checkClosest(this->getUser(), bleppo);

		//Debug - print the closest object name
		if (obj != nullptr)
			std::cout << "closest: " << obj->getName() << std::endl;
		else
			std::cout << "No Collision: " << std::endl;
	
			
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
