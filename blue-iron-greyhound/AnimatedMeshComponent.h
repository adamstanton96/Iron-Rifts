#pragma once
/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com"(recursiveNodeProcess,AnimNodeProcess)
////////////////////////////////////
#include "MeshComponent.h"
#include "AssimpLoader.h"
#include <vector>

#include "bone.h"
#include "node.h"
#include "animNode.h"
#include"skeleton.h"
class skeleton;

class AnimatedMeshComponent : public MeshComponent
{
public:

	AnimatedMeshComponent(string Name);
	AnimatedMeshComponent();

	void update();

	void loadObject(const char * filename);

	void AddAnimation(animation& in_anim);
	animation* FindAnimation(std::string anim_to_find);
	void PlayAnimation(animation& anim, bool loop = false, bool reset_to_start = false);
	void StopAnimating();

	//Temporary hopefully
	void setSkeletonDeltaTime(double dt)
	{
		sceneLoaderSkeleton->setDeltaTime(dt);
	}


	std::vector<glm::mat4> getBoneMats()
	{
		return sceneLoaderSkeleton->getBoneMats();
	}

	
private:

	skeleton* sceneLoaderSkeleton;

	std::vector<node*> nodes;
	std::vector<animNode*> animNodes;


	std::vector<bone*> bones;

	glm::mat4 globalInverseTransform;

	std::vector<animation> animations;

	animation* Anim_Test_Idle;
	animation* Anim_Test_Walk;
};