#include "SDL.h"
#include <glm/glm.hpp>


#include "OpenglRenderer.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "MovementComponent.h"
#include "SDLInputSystem.h"


#include "RigidBodyComponent.h"
#include "CollisionSystem.h"





#include "ObjectFactory.h"

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::init()
{
	//camera set up

	Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 10.0f, 30.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), 0.0);
	//Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 2.0f, 30.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), 0.0);
	cameraComponent->init();

	//First Object - Acting as player (camera component / movement component)
	GameObject *Player = new GameObject("player");
	Player->setTranslation(glm::vec3(-5.0f, 0.0f, 60.0f));
	Player->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	Player->setCameraRotation(0.0);
	Player->setRenderRotateVec(glm::vec3(0, -1, 0));
	Player->setRenderRotateDeg(0);

	RigidBodyComponent* rigidBody = new RigidBodyComponent("Rigid Body");
	Player->addComponent(rigidBody);
	rigidBody->setCollisionSystem(getSystem<CollisionSystem>());
	rigidBody->setBodyType("DYNAMIC");

	MeshComponent* meshComponent = new MeshComponent("sphere");
	Player->addComponent(meshComponent);
	meshComponent->setRenderer(getSystem<RenderingSystem>());
	meshComponent->loadObject("../../assets/AlienPlanet2.dae");
	meshComponent->loadTexture("../../assets/tex/scifiFloor.bmp");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(getSystem<InputSystem>());

	Player->addComponent(cameraComponent);
	Player->addComponent(moveComponent);





	objectMap.insert(objects("Player", Player));
}

void ObjectFactory::addSystem(System * system)
{
	systemList.push_back(system);
}

GameObject * ObjectFactory::createObject(std::string input, glm::vec3 position, float rotation)
{
	GameObject * newObject = objectMap[input];
	return newObject;
}

void ObjectFactory::initSystems()
{
}

void ObjectFactory::initObjects()
{

}
