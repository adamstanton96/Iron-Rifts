#include "MechanicsComponent.h"

MechanicsComponent::MechanicsComponent(std::string name)
{
	this->name = name;
}

MechanicsComponent::~MechanicsComponent()
{
}

void MechanicsComponent::init()
{
	this->health = 100;
	this->damage = 5;
}

void MechanicsComponent::update()
{
	//Check for input... Change input to mouse click once inputsystem is updated.
	if (this->input->keyPressed("P"))
		fireWeapon();
}

void MechanicsComponent::fireWeapon()
{
	printf("Shooty Shooty! \n"); //Testing
}

void MechanicsComponent::setInput(InputSystem * newInput)
{
	this->input = newInput;
}

void MechanicsComponent::setAudio(AudioSystem * newAudio)
{
	this->audio = newAudio;
}
