#pragma once
#include <vector>
#include <glm/glm.hpp>


class node
{
public:
	std::string name;
	glm::mat4 transformation;
	node* parent;
	int numOfChildren;
	std::vector<node*> children;
	int numOfMeshes;
	int MeshIDs;
	//metaData...

	std::string parentName;
	std::vector<std::string> childrenNames;
private:


};

