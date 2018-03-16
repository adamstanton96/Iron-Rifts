#include "AnimatedMeshComponent.h"


AnimatedMeshComponent::AnimatedMeshComponent(string Name)
{
	isAnimated = true;

	Anim_Test_Idle = new animation("Idle", FramesToTime(glm::vec2(51, 110)), 2);
	Anim_Test_Walk = new animation("Walk", FramesToTime(glm::vec2(1, 40)), 2);

}

AnimatedMeshComponent::AnimatedMeshComponent()
{

}



void AnimatedMeshComponent::update()
{

	sceneLoaderSkeleton->update();
	
	sceneLoaderSkeleton->SetIdleAnimation(Anim_Test_Idle);
		
	//The true is for loop, and the false is for reset_to_start.
	PlayAnimation(*Anim_Test_Walk, true, false);
	///PlayAnimation(*Anim_Test_Idle, true, false)

	MeshComponent::update();
}



void AnimatedMeshComponent::loadObject(const char * filename)
{
	vector<glm::vec3> minmax;

	AssimpLoader::loadObjectDataAnimations(filename, meshIDs, indexCounts, minmax, nodes, animNodes, bones);

	setMinMax(minmax);

	globalInverseTransform = glm::inverse(nodes[0]->transformation);
	sceneLoaderSkeleton = new skeleton(bones, globalInverseTransform);
}


void AnimatedMeshComponent::AddAnimation(animation& in_anim)
{
	animations.push_back(in_anim);
}

animation* AnimatedMeshComponent::FindAnimation(std::string anim_to_find)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations.at(i).name == anim_to_find)
			return &animations.at(i);
	}
	return nullptr;
}

void AnimatedMeshComponent::PlayAnimation(animation& anim, bool loop, bool reset_to_start)
{
	sceneLoaderSkeleton->PlayAnimation(anim, loop, reset_to_start);
}

void AnimatedMeshComponent::StopAnimating()
{
	sceneLoaderSkeleton->StopAnimating();
}