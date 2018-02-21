#pragma once
/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com"(recursiveNodeProcess,AnimNodeProcess)
////////////////////////////////////
#include "MeshComponent.h"
#include "AssimpLoader.h"
#include <vector>
#include "bone.h"

class AnimatedMeshComponent : public MeshComponent
{
public:

	AnimatedMeshComponent(string Name) 
	{
		isAnimated = true;
	}

	AnimatedMeshComponent() 
	{
		
	}
	
	void loadObject(const char * filename)
	{
		vector<glm::vec3> minmax;

		AssimpLoader::loadObjectDataAnimations(filename, meshIDs, indexCounts, minmax, ai_nodes, ai_nodes_anim, bones);

		setMinMax(minmax);
	}


	//class node
	//{
	//public:
	//	string name;
	//	glm::mat4 transformation;
	//	node* parent;
	//	int numOfChildren;
	//	std::vector<node*> children;
	//	int numOfMeshes;
	//	int MeshIDs;
	//	//metaData...
	//private:


	//};

	//class animNode
	//{
	//public:
	//	string nodeName;
	//	int numPositionKeys;
	//	std::vector<glm::vec3> positionKeys;

	//	int numRotationKeys;
	//	std::vector<glm::vec3> rotationKeys;

	//	int numScalingKeys;
	//	std::vector<glm::vec3> scalingKeys;
	//private:


	//};


	
private:
	std::vector<aiNode*> ai_nodes;
	std::vector<aiNodeAnim*> ai_nodes_anim;


	std::vector<bone*> bones;

	glm::mat4 globalInverseTransform;


};