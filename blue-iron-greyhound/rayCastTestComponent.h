#pragma once
#include "Component.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "IronRiftsPhysicsSystem.h"

#define DEG_TO_RADIAN 0.017453293

class RayCastTestComponent : public Component
{
public:
	RayCastTestComponent(std::string name);
	~RayCastTestComponent();

	void init();
	void update();

	void setInput(InputSystem *newInput);
	void setPhysics(PhysicsSystem *newPhysics);
private:
	InputSystem *input;
	PhysicsSystem *physics;
};
