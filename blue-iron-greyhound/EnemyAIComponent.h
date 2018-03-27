#pragma once
#include "Component.h"
#include "GameObject.h"
#include "AISystem.h"


class EnemyAIComponent : public Component
{
public:
	EnemyAIComponent();
	~EnemyAIComponent() {}

	void init();
	void update();

	
	void setAIsystem(AISystem*);

	void moveTowards(glm::vec2 goal);

private:
	AISystem* AIsystem;

	glm::vec3 velocity;

	std::vector<glm::vec3> currentRoute;
	glm::vec3 currentGoalPosition;

	bool atFinalDestination;
	int goalNodeIndex;

	int targetIndex;

	std::vector<glm::vec3> targets;

};