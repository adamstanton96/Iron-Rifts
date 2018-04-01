#pragma once
#include "System.h"
#include "AstarGraph.h"
#include "aStarPathFinder.h"


class AISystem : public System
{
public:
	AISystem();
	~AISystem() {}

	void init();
	void addPathGraph(AstarGraph* graph);
	
	std::vector<glm::vec3> findPath(glm::vec2 currPos, glm::vec2 target);

private:
	AstarGraph* mapPath;
	aStarPathFinder AstarAlgorithm;
};