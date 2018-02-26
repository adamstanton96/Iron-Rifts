#include "MeshComponent.h"
#include "OpenglRenderer.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"


MeshComponent::MeshComponent(std::string name)
{
	isAnimated = false;
}

void MeshComponent::init()
{
	
}


//update all orientation values and then draw mesh
void MeshComponent::update()
{
	renderer->draw(this);

	scaling = getUser()->getScaling();

	translation = getUser()->getPosition();
	rotate = getUser()->getRotationAxis();
	deg = this->user->getRotationDegrees();

}


	


//sends file name to renderer which will load texture and push it into the texture vector.
///This design is probably pretty bad. renderer could return the generated texture ID
/// rather than us sending it a pointer back to this mesh instance.
void MeshComponent::loadTexture(char * filename)
{
	renderer->loadTexture(this, filename);
}

//Loads an object file. AnimatedMeshComponent inherits from this class and has it's own loadObject() function
void MeshComponent::loadObject(const char * filename)
{
		vector<glm::vec3> minmax;

		AssimpLoader::loadObjectData(filename, meshIDs, indexCounts, minmax);

		this->setMinMax(minmax);

}


void MeshComponent::setRenderer(RenderingSystem* rendersystem)
{
	renderer = rendersystem;
}

//If the user of this mesh has a rigid body we give that rigid body the min and max
//that LoadObject generated from the model.
void MeshComponent::setMinMax(vector<glm::vec3> minmax)
{

	RigidBodyComponent* body = getUser()->getComponent<RigidBodyComponent>();
	glm::vec3 scale = getUser()->getScaling();

	if(body != NULL)
	body->setboundingVolume(minmax[0] * scale, minmax[1] * scale);


	
}


//Meshes get/set
void MeshComponent::setMeshes(vector<int> meshIDs)
{
	this->meshIDs = meshIDs;
}

vector<int> MeshComponent::getMeshes()
{
	return meshIDs;
}



//Textures get
vector<int> MeshComponent::getTextures()
{
	return textures;
}

//Indices get/set
void MeshComponent::setIndexCounts(vector<int> indexCounts)
{
	this->indexCounts = indexCounts;
}

vector<int> MeshComponent::getIndexCounts()
{
	return indexCounts;
}


//orientation sets/gets
void MeshComponent::setTranslation(glm::vec3 tran)
{
	translation = tran;
}

void MeshComponent::setScaling(glm::vec3 scale)
{
	scaling = scale;
}


glm::vec3 MeshComponent::getTranslation()
{
	return translation;
}

glm::vec3 MeshComponent::getRotate()
{
	return rotate;

}
glm::vec3 MeshComponent::getScaling()
{
	return scaling;
}


