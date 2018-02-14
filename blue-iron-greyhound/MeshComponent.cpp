#include "MeshComponent.h"
#include "OpenglRenderer.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
class RigidBodyComponent;

MeshComponent::MeshComponent(std::string name)
{
	isAnimated = false;
}

void MeshComponent::init()
{
	
}



void MeshComponent::update()
{
	renderer->draw(this);

	scaling = getUser()->getScaling();
	translation = getUser()->getTranslation();
	rotate = getUser()->getRenderRotate();
	deg = this->user->getRenderRotateDeg();
}


void MeshComponent::loadTexture(char * filename)
{
	renderer->loadTexture(this, filename);
}

void MeshComponent::loadObject(const char * filename)
{
	renderer->loadObject(this, filename);
}

void MeshComponent::setRenderer(RenderingSystem* rendersystem)
{
	renderer = rendersystem;
}


void MeshComponent::setMinMax(vector<glm::vec3> minmax)
{

	RigidBodyComponent* body = getUser()->getComponent<RigidBodyComponent>();
	glm::vec3 scale = getUser()->getScaling();

	if(body != NULL)
	body->setboundingVolume(minmax[0] * scale, minmax[1] * scale);


	
}



void MeshComponent::setMeshes(vector<int> meshIDs)
{
	this->meshIDs = meshIDs;
}

vector<int> MeshComponent::getMeshes()
{
	return meshIDs;
}

vector<int> MeshComponent::getTextures()
{
	return textures;
}

void MeshComponent::setIndexCounts(vector<int> indexCounts)
{
	this->indexCounts = indexCounts;
}

vector<int> MeshComponent::getIndexCounts()
{
	return indexCounts;
}



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


