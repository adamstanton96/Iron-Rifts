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

		glm::vec3 userPos = this->getUser()->getPosition();

		//Calculate the rays direction
		glm::vec3 forward(0, 0, -1);
		glm::vec3 up(0, 1, 0);

		double theta = (this->getUser()->getRotationDegrees()* DEG_TO_RADIAN );	//The minus was an attempt to fix the collision inaccuracy

		double cos_thetaf = cos(theta);
		glm::vec3 cos_theta(cos(theta));
		glm::vec3 sin_theta(sin(theta));

		glm::dvec3 rotatedDirectionVector = (forward * cos_theta) + (glm::cross(up, forward) * sin_theta) + (up * glm::dot(up, forward)) * glm::vec3((1 - cos_thetaf));
		rotatedDirectionVector = glm::vec3(rotatedDirectionVector.x, rotatedDirectionVector.y, -rotatedDirectionVector.z);

		//Find the two points defining our ray 
		Ray blappo = physics->castRay(userPos, rotatedDirectionVector, 50.0f);

		//Get all objects in the pathh of the ray
		std::vector<GameObject*> objectCollisions = physics->checkRayCollision(blappo);

		//Find out which collided object is closest to the player
		GameObject* obj = nullptr;

		if (objectCollisions.size() != 0)
		obj = physics->checkClosest(this->getUser(), objectCollisions);

		//Debug - print the closest object name
		if (obj != nullptr)
			std::cout << "closest: " << obj->getName() << std::endl;
		else
			std::cout << "No Collision: " << std::endl;
	
			

		//Emit bullet particle (graphics). the position needed to be offset so it came from the center of the current test cube in use and not fired from the corner
		bulletRender->emit(glm::vec3(userPos.x - 1, userPos.y, userPos.z + 1), rotatedDirectionVector, glm::vec3(0.3));
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

void RayCastTestComponent::setRenderer(bulletParticles* newRenderer)
{
	this->bulletRender = newRenderer;
}
