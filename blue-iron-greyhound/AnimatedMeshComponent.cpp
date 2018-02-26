#include "AnimatedMeshComponent.h"


AnimatedMeshComponent::AnimatedMeshComponent(string Name)
{
	isAnimated = true;
}

AnimatedMeshComponent::AnimatedMeshComponent()
{

}


static animation Anim_Test_Idle("Idel_Animation___0_pose_matrix", FramesToTime(glm::vec2(0, 110)), 2);
//static animation Anim_Test_Walk("Walk", FramesToTime(glm::vec2(1, 45)), 2);


void AnimatedMeshComponent::update()
{
	MeshComponent::update();

	sceneLoaderSkeleton->update();

	sceneLoaderSkeleton->SetIdleAnimation(&Anim_Test_Idle);

	
		
	//The true is for loop, and the false is for reset_to_start.
	PlayAnimation(Anim_Test_Idle, true, true);
	
	


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