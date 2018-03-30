#pragma once
#include "Component.h"

class bulletParticles : public Component
{
	bulletParticles();
	~bulletParticles();

	void init();
	void update();
};
