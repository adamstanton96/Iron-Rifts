#pragma once
#include "MechanicsComponent.h"

class PlayerMechanicsComponent : public MechanicsComponent
{
public:
	PlayerMechanicsComponent(std::string name);
	~PlayerMechanicsComponent();

	void init();
	void update(double dt);

	void fireWeapon();
};
