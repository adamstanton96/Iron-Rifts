#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>


class node
{
public:
	std::string name;
	aiMatrix4x4 transformation;
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

