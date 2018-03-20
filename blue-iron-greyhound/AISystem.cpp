#include "AISystem.h"


AISystem::AISystem()
{

}



void AISystem::init()
{

}

std::vector<glm::vec2> AISystem::findPath(glm::vec2 currPos, glm::vec2 target)
{
	int startNode;
	int goalNode;

	int closestNode;
	float closestNodeDist = 9999;
	
	//find cloest start node
	for (int i = 0; i < mapPath->nodes.size(); i++)
	{
		 //closestNode;
		 closestNodeDist = 9999;

		if (glm::distance(mapPath->nodes[i]->getPos(), currPos) < closestNodeDist)
		{
			closestNode = i;
		}
	}

	startNode = closestNode;

	//find cloest target node
	for (int i = 0; i < mapPath->nodes.size(); i++)
	{
		// closestNode;
		 closestNodeDist = 9999;

		if (glm::distance(mapPath->nodes[i]->getPos(), target) < closestNodeDist)
		{
			closestNode = i;
		}
	}

	goalNode = closestNode;

	std::vector<node*> pathway = AstarAlgorithm.AStarAlgorithm(*mapPath, startNode, goalNode);

	std::vector<glm::vec2> path;
	for (int i = 0; i < pathway.size(); i++)
	{
		path.push_back(pathway[i]->getPos());
	}

	return path;
}


void AISystem::addPathGraph(AstarGraph* graph)
{
	mapPath = graph;
}