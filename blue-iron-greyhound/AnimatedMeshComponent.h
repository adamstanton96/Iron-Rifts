#pragma once
#include "MeshComponent.h"
#include <vector>

class AnimatedMeshComponent : public MeshComponent
{
public:

	AnimatedMeshComponent(string Name) : MeshComponent(Name)
	{
		isAnimated = true;
	}


	void loadBoneData()
	{
		//AssimpLoader::loadBoneData("../../assets/RobotAnimated.dae");
	}

	void setSkeletalData()
	{

	}


private:



};