#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include "AISystem.h"


class EnemyAIComponent : public Component
{
public:
	EnemyAIComponent();
	~EnemyAIComponent() {}

	void init();
	void update();

	void setCollisionSystem(PhysicsSystem*);
	void setAIsystem(AISystem*);


private:
	PhysicsSystem* collisionSys;
	AISystem* AIsystem;

	glm::vec3 velocity;

	std::vector<glm::vec2> currentRoute;

	bool newDestination;


};