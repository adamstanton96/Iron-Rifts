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

	AnimatedMeshComponent(string Name) 
	{
		isAnimated = true;
	}

	AnimatedMeshComponent() 
	{
		
	}

	void update()
	{
		MeshComponent::update();

		sceneLoaderSkeleton->update();
		//cout << "bone update" << endl;
	}


	
	void loadObject(const char * filename)
	{
		vector<glm::vec3> minmax;

		AssimpLoader::loadObjectDataAnimations(filename, meshIDs, indexCounts, minmax, nodes, animNodes, bones);

		setMinMax(minmax);

		sceneLoaderSkeleton = new skeleton(bones, globalInverseTransform);
	}




	
private:

	skeleton* sceneLoaderSkeleton;

	std::vector<node*> nodes;
	std::vector<animNode*> animNodes;


	std::vector<bone*> bones;

	glm::mat4 globalInverseTransform;


};