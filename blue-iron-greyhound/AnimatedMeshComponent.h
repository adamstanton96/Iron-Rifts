#pragma once
/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com"(recursiveNodeProcess,AnimNodeProcess)
////////////////////////////////////
#include "MeshComponent.h"
#include "AssimpLoader.h"
#include <vector>
#include "bone.h"

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
		ai_nodes = nodes;
	}

	void setAnimNodes(std::vector<aiNodeAnim*> animNodes)
	{
		ai_nodes_anim = animNodes;

		// globalInverseTransform = glm::inverse(AssimpLoader::AiToGLMMat4(ai_nodes[0]->mTransformation));
	}

	void addBones(std::vector<bone*> bone)
	{
		//bones.push_back(bone);
		bones = bone;

		for (int i = 0; i < bones.size(); i++)
		{
			std::cout << "Bone " << bones[i]->id << " " << bones[i]->name << std::endl;
		}

	/*	for (int i = 0; i < ai_nodes.size(); i++)
		{
			aiNode* node = ai_nodes[i];
			std::cout << "Bone " << bones[i]->id << " " << bones[i]->name << std::endl;
		}*/
		
	}


private:
	std::vector<aiNode*> ai_nodes;
	std::vector<aiNodeAnim*> ai_nodes_anim;

	std::vector<bone*> bones;

	glm::mat4 globalInverseTransform;


};