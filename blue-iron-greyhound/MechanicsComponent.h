/*=============================================================================
* MechanicsComponent.h
* Author: Adam Stanton
* Used to define how our game objects interact with the game...
=============================================================================*/

#pragma once
#include "Component.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "AudioSystem.h"

class MechanicsComponent : public Component
{
public:
	MechanicsComponent(std::string name);
	~MechanicsComponent();

	void init();
	void update();

	void fireWeapon();
	

	void setInput(InputSystem *newInput);
	void setAudio(AudioSystem *newAudio);
private:
	int health, damage;

	InputSystem *input;
	AudioSystem *audio;
};
