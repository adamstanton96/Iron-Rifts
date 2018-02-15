#pragma once
/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com"(recursiveNodeProcess,AnimNodeProcess)
////////////////////////////////////
#include "MeshComponent.h"
#include "AssimpLoader.h"
#include <vector>

class AnimatedMeshComponent// : public MeshComponent
{
public:

	AnimatedMeshComponent(string Name) //: MeshComponent(Name)
	{
		//isAnimated = true;
	}

	AnimatedMeshComponent() {}
	



	void setAiNodes(std::vector<aiNode*> nodes)
	{
		this->ai_nodes = nodes;
	}

	void setAnimNodes(std::vector<aiNodeAnim*> animNodes)
	{
		this->ai_nodes_anim = animNodes;
	}


private:
	std::vector<aiNode*> ai_nodes;
	std::vector<aiNodeAnim*> ai_nodes_anim;


};