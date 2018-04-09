#include "PlayerMechanicsComponent.h"

PlayerMechanicsComponent::PlayerMechanicsComponent(std::string name)
{
	this->name = name;
}

PlayerMechanicsComponent::~PlayerMechanicsComponent()
{

}

void PlayerMechanicsComponent::init()
{
	this->health = 100;
	this->damage = 5;
	this->weaponRange = 50;
	this->rateOfFire = 0.1;
	this->cooldownTimer = 0;
}

void PlayerMechanicsComponent::update(double dt)
{
	cooldownTimer += dt;

	if (this->health <= 0)
	{
		std::cout << this->user->getName() << " Is Dead!" << std::endl; //Testing
	}
	
	//Check for input... Change input to mouse click once inputsystem is updated.
	if (this->input->keyPressed("R"))
	{
		if (cooldownTimer > rateOfFire)
		{
			fireWeapon(dt);
			cooldownTimer = 0;
		}	
	}	
}

void PlayerMechanicsComponent::fireWeapon(double dt)
{
	//printf("Shooty Shooty! \n"); //Testing
	//audio->playAudio("../../assets/audio/bell.wav");

	int bulletVelocity = 100;

	
	//Calculate the rays direction
	glm::vec3 forward(0, 0, -1);
	glm::vec3 up(0, 1, 0);

	double theta = (this->getUser()->getRotationDegrees()* DEG_TO_RADIAN);	//The minus was an attempt to fix the collision inaccuracy

	double cos_thetaf = cos(theta);
	glm::vec3 cos_theta(cos(theta));
	glm::vec3 sin_theta(sin(theta));

	glm::dvec3 rotatedDirectionVector = (forward * cos_theta) + (glm::cross(up, forward) * sin_theta) + (up * glm::dot(up, forward)) * glm::vec3((1 - cos_thetaf));
	rotatedDirectionVector = glm::vec3(rotatedDirectionVector.x, rotatedDirectionVector.y, -rotatedDirectionVector.z);

	//Find the two points defining our ray 
	Ray weaponRay = physics->castRay(this->getUser()->getPosition(), rotatedDirectionVector, weaponRange);

	//Get all objects in the path of the ray
	std::vector<GameObject*> potentialHits = physics->checkRayCollision(weaponRay);

	//Find out which collided object is closest to the player
	GameObject* obj = nullptr;

	if (potentialHits.size() != 0)
		obj = physics->checkClosest(this->getUser(), potentialHits);

	//Debug - print the closest object name
	if (obj != nullptr)
	{
		std::cout << "closest: " << obj->getName() << std::endl;

		MechanicsComponent * comp = obj->getComponent<MechanicsComponent>();
		if (comp != nullptr)
		{
			comp->setHealth(comp->getHealth() - this->damage);
			std::cout << comp->getUser()->getName() << "health: " << comp->getHealth();
		}
	}
	else
	{
		std::cout << "No Collision: " << std::endl;
	}

	//Emit bullet - If its going to hit something, set the distance so it stops when it hits.
	if (obj != nullptr)
		particleRenderer->emit(this->getUser()->getPosition(), rotatedDirectionVector, glm::vec3(bulletVelocity*dt), glm::distance(this->getUser()->getPosition(), obj->getPosition()));
	else
		particleRenderer->emit(this->getUser()->getPosition(), rotatedDirectionVector, glm::vec3(bulletVelocity*dt), weaponRange);

	start = std::clock();
}