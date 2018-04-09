/*=============================================================================
* Project: Blue Iron Greyhound
* Adam Stanton, Chloe Madden, Paul McLaughlin, Thomas Mackrell.
=============================================================================*/

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

//Asset pathway:
/// ../../assets/

#include "SDL.h"
#include <glm/glm.hpp>

//Graphics
#include "OpenglRenderer.h"
#include "ParticleRenderer.h"

//Input
#include "MovementComponent.h"
#include "SDLInputSystem.h"

//misc
#include "GameObject.h"
#include "CameraComponent.h"

//Weapon fire
#include "rayCastTestComponent.h"
#include "BulletParticle.h"

//physics
#include "RigidBodyComponent.h"
#include "CollisionSystem.h"
#include "IronRiftsPhysicsSystem.h"

//AI
#include "AISystem.h"
#include "AstarGraph.h"
#include "EnemyAIComponent.h"

//audio
#include "AudioTestComponent.h"
#include "IrrKlangAudioSystem.h"

//HUD
#include "HUD.h"


//timer
#include <ctime>
#include <cstdlib>
#include "time.h"

// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
std::clock_t start;
double dt;


int main(int argc, char *argv[])
{
	//Input System
	InputSystem *inputSystem = new SDLInputSystem();
	inputSystem->init();


	//physics system.
	PhysicsSystem* collisionsystem = new IronRiftsPhysicsSystem();

	IrrKlangAudioSystem * audioSystem = new IrrKlangAudioSystem("audioSystem");
	audioSystem->init();

	//camera set up
	Camera *cameraComponent = new Camera("camera");
	cameraComponent->setEye(glm::vec3(-2.0f, 2.0f, 30.0f));
	cameraComponent->setAt(glm::vec3(0.0f, 1.0f, -1.0f));
	cameraComponent->setUp(glm::vec3(0.0f, 1.0f, -1.0f));
	cameraComponent->setRotation(0.0f);
	cameraComponent->setInput(inputSystem);
	cameraComponent->init();

	//Render System
	RenderingSystem* renderer = new openglRenderer();
	renderer->camera = cameraComponent;

	
	//Temporarily hold all objects so that main isn't so awkward
	std::vector<GameObject*> objectList;
	
	//hud
	HUD  *h = new HUD();
	h->update();
	////////////////////////////////////////////////////
	//First Object - Acting as player (camera component / movement component)
	GameObject *Player = new GameObject("player");
	Player->setPosition(glm::vec3(5.0f, 0.0f, 60.0f));
	Player->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	Player->setRotationAxis(glm::vec3(0, -1, 0));
	Player->setRotationDegrees(0);

	RigidBodyComponent* rigidBody = new RigidBodyComponent("Rigid Body");
	Player->addComponent(rigidBody);
	rigidBody->setCollisionSystem(collisionsystem);
	rigidBody->setBodyType("DYNAMIC");
	rigidBody->setBoundingType("OBB");

	MeshComponent* meshComponent = new MeshComponent("PlayerMesh");
	Player->addComponent(meshComponent);
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("../../assets/blenderTest.dae");
	meshComponent->loadTexture("../../assets/tex/habitatWater.bmp");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);

	AudioTester *audioTester = new AudioTester("audioTester");
	audioTester->setAudio(audioSystem);
	audioTester->setInput(inputSystem);

	Player->addComponent(audioTester);
	Player->addComponent(cameraComponent);
	Player->addComponent(moveComponent);

	//Bullet Particle System
	ParticleRenderer* particleRender = new ParticleRenderer(cameraComponent);
	particleRender->init();

	//bullet itself
	bulletParticle* bullet = new bulletParticle(glm::vec4(1, 0.5f, 0.5f,1.0f), 200, "../../assets/tex/rainTex.png", particleRender); //(colour, numOfParticles, texture, ParticleRenderer)
	bullet->init();
	Player->addComponent(bullet);

	//Raycast
	RayCastTestComponent *raycasttester = new RayCastTestComponent("Raycaster");
	raycasttester->setRenderer(bullet);
	raycasttester->setInput(inputSystem);
	raycasttester->setPhysics(collisionsystem);
	Player->addComponent(raycasttester);

	objectList.push_back(Player);

	////////////////////////////////////////////////////
	//AI system and pathfinding/////////////////////////
	EnemyAIComponent* EnemyAI = new EnemyAIComponent();

	typedef std::pair<int, int> path;
	int names[] = { 0,1,2,3,4 };
	glm::vec2 locations[] = { { 0,0 },{ 30,0 },{ 30,-30 },{ 0,-30 },{ 0,0 } };
	std::pair<int, int> edges[] = { path(0,1),path(1,2),path(2,3),path(3,4), path(4,0) };
	float weights[] = { 1, 1, 1, 1, 1 };

	AISystem* AiSys = new AISystem();
	AstarGraph* graph = new AstarGraph(names, locations, edges, weights, 5, 5);

	AiSys->addPathGraph(graph);
	EnemyAI->setAIsystem(AiSys);
	EnemyAI->init();

	//AI test object (enemy Player)
	//Green Demo Cube
	GameObject *Enemey = new GameObject("Enemy AI Cube");
	Enemey->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	Enemey->setScaling(glm::vec3(2, 2, 2));
	Enemey->setRotationAxis(glm::vec3(0, 1, 0));
	Enemey->setRotationDegrees(0);

	Enemey->addComponent(EnemyAI);

	RigidBodyComponent* EnemeyRigidBody = new RigidBodyComponent("Rigid Body");
	Enemey->addComponent(EnemeyRigidBody);
	EnemeyRigidBody->setCollisionSystem(collisionsystem);
	EnemeyRigidBody->setBodyType("DYNAMIC");
	EnemeyRigidBody->setBoundingType("OBB");

	MeshComponent* EnemeyMesh = new MeshComponent("test");
	Enemey->addComponent(EnemeyMesh);
	EnemeyMesh->setRenderer(renderer);
	EnemeyMesh->loadObject("../../assets/blenderTest.dae");
	EnemeyMesh->loadTexture("../../assets/tex/grass.bmp");

	objectList.push_back(Enemey);
	////////////////////////////////////////////////////


	//Green Demo Cube
	GameObject *barrier2 = new GameObject("Green Cube");
	barrier2->setPosition(glm::vec3(5.0f, -5.0f, 50.0f));
	barrier2->setScaling(glm::vec3(2.0f, 2.0f, 2.0f));
	barrier2->setRotationAxis(glm::vec3(0, 1, 0));
	barrier2->setRotationDegrees(45);

	RigidBodyComponent* rigidBody3 = new RigidBodyComponent("Rigid Body");
	barrier2->addComponent(rigidBody3);
	rigidBody3->setCollisionSystem(collisionsystem);
	rigidBody3->setBodyType("STATIC");
	rigidBody3->setBoundingType("OBB");

	MeshComponent* barriermesh2 = new MeshComponent("test");
	barrier2->addComponent(barriermesh2);
	barriermesh2->setRenderer(renderer);
	barriermesh2->loadObject("../../assets/blenderTest.dae");
	barriermesh2->loadTexture("../../assets/tex/grass.bmp");

	objectList.push_back(barrier2);


	//Blue Demo Cube
	GameObject *barrier = new GameObject("Blue Cube");
	barrier->setPosition(glm::vec3(-15.0f, -5.0f, 100.0f));
	barrier->setScaling(glm::vec3(5.5f, 5.5f, 5.5f));
	barrier->setRotationAxis(glm::vec3(1, 0, 0));
	barrier->setRotationDegrees(0);

	RigidBodyComponent* rigidBody2 = new RigidBodyComponent("Rigid Body");
	barrier->addComponent(rigidBody2);
	rigidBody2->setCollisionSystem(collisionsystem);
	rigidBody2->setBodyType("STATIC");
	rigidBody2->setBoundingType("OBB");

	MeshComponent* barriermesh = new MeshComponent("test");
	barrier->addComponent(barriermesh);
	barriermesh->setRenderer(renderer);
	barriermesh->loadObject("../../assets/blenderTest.dae");
	barriermesh->loadTexture("../../assets/tex/habitatWater.bmp");

	objectList.push_back(barrier);


	//Brown Demo Cube
	GameObject *Raycast = new GameObject("Brown Cube");
	Raycast->setPosition(glm::vec3(5.0f, -5.0f, 140.0f));
	Raycast->setScaling(glm::vec3(5.5f, 5.5f, 5.5f));
	Raycast->setRotationAxis(glm::vec3(0, 1, 0));
	Raycast->setRotationDegrees(45);

	RigidBodyComponent* RaycastRigid = new RigidBodyComponent("Rigid Body");
	Raycast->addComponent(RaycastRigid);
	RaycastRigid->setCollisionSystem(collisionsystem);
	RaycastRigid->setBodyType("STATIC");
	RaycastRigid->setBoundingType("OBB");

	MeshComponent* RaycastMesh = new MeshComponent("test");
	Raycast->addComponent(RaycastMesh);
	RaycastMesh->setRenderer(renderer);
	RaycastMesh->loadObject("../../assets/blenderTest.dae");
	RaycastMesh->loadTexture("../../assets/tex/habitatWood2.bmp");

	objectList.push_back(Raycast);


	//Grey Demo Cube
	GameObject *Raycast2 = new GameObject("Grey Cube");
	Raycast2->setPosition(glm::vec3(-15.0f, -5.0f, 140.0f));
	Raycast2->setScaling(glm::vec3(5.5f, 5.5f, 5.5f));
	Raycast2->setRotationAxis(glm::vec3(0, 1, 0));
	Raycast2->setRotationDegrees(45);

	RigidBodyComponent* Raycast2Rigid = new RigidBodyComponent("Rigid Body");
	Raycast2->addComponent(Raycast2Rigid);
	Raycast2Rigid->setCollisionSystem(collisionsystem);
	Raycast2Rigid->setBodyType("STATIC");
	Raycast2Rigid->setBoundingType("OBB");

	MeshComponent* Raycast2Mesh = new MeshComponent("test");
	Raycast2->addComponent(Raycast2Mesh);
	Raycast2Mesh->setRenderer(renderer);
	Raycast2Mesh->loadObject("../../assets/blenderTest.dae");
	Raycast2Mesh->loadTexture("../../assets/plainbuilding/iron.bmp");

	objectList.push_back(Raycast2);
	/////////////////////////////////////////////////////////////////




	//Ground Plane
	GameObject *GroundPlane = new GameObject("Ground Plane");
	GroundPlane->setPosition(glm::vec3(0.0f, -5.0f, -60.0f));
	GroundPlane->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane->setRotationAxis(glm::vec3(NULL, NULL, NULL));
//	RigidBodyComponent* rigidBody4 = new RigidBodyComponent("Rigid Body");
//	GroundPlane->addComponent(rigidBody4);
//	rigidBody4->setCollisionSystem(collisionsystem);
//	rigidBody4->setBodyType("STATIC");
	MeshComponent* secondMesh = new MeshComponent("cube");
	GroundPlane->addComponent(secondMesh);
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("../../assets/cube_with_2UVs.DAE");
	secondMesh->loadTexture("../../assets/tex/rockyground.bmp");
	
	objectList.push_back(GroundPlane);

	//Ground Plane 2
	GameObject *GroundPlane2 = new GameObject("Ground Plane");
	GroundPlane2->setPosition(glm::vec3(0.0f, -5.0f, 60.0f));
	GroundPlane2->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane2->setRotationAxis(glm::vec3(NULL, NULL, NULL));
	//RigidBodyComponent* rigidBody5 = new RigidBodyComponent("Rigid Body");
	//GroundPlane2->addComponent(rigidBody5);
	//rigidBody5->setCollisionSystem(collisionsystem);
	//rigidBody5->setBodyType("STATIC");
	MeshComponent* secondMesh2 = new MeshComponent("cube");
	GroundPlane2->addComponent(secondMesh2);
	secondMesh2->setRenderer(renderer);
	secondMesh2->loadObject("../../assets/cube_with_2UVs.DAE");
	secondMesh2->loadTexture("../../assets/tex/rockyground.bmp");

	objectList.push_back(GroundPlane2);


	//Test function for new getcomponent.
	///std::cout << Player->getComponent<MeshComponent>()->getName() << std::endl;

	bool running = true;

	SDL_Event sdlEvent;
	do
	{
		//start timer 
		start = std::clock();

		while (SDL_PollEvent(&sdlEvent)) //This poll event should not be here since it couples the main to SDL. 
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				running = false;
			}
		}


		
		renderer->clearScreen();

		//Update all objects
		for (unsigned int i = 0; i < objectList.size(); i++)
		{
			objectList[i]->update();
		}

		renderer->swapBuffers();


 
		//Stores the time past the frame has taken to complete
		dt = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	
	} while (running);


	//delete all the objects
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		delete objectList[i];
	}

	return 0;
}



//Models not currently getting used
/*
	GameObject *plainBuilding = new GameObject("old building");
	plainBuilding->setTranslation(glm::vec3(-15.0f, 1.0f, 50.0f));
	plainBuilding->setScaling(glm::vec3(5.0f, 5.0f, 5.0f));
	plainBuilding->setRenderRotate(glm::vec3(0, 0, 0));

	MeshComponent* plainBuildingMesh = new MeshComponent("test");
	plainBuilding->addComponent(plainBuildingMesh);
	plainBuildingMesh->setRenderer(renderer);
	//testmesh1->loadObject("plainbuilding.obj");
	
	//ground
	plainBuildingMesh->loadTexture("plainbuilding/brack.bmp");
	//lower windows
	plainBuildingMesh->loadTexture("plainbuilding/window1.bmp");
	//main windows
	plainBuildingMesh->loadTexture("plainbuilding/window2.bmp");
	//upper windows
	plainBuildingMesh->loadTexture("plainbuilding/window3.bmp");
	//??
	plainBuildingMesh->loadTexture("plainbuilding/wf.bmp");
	//brick
	plainBuildingMesh->loadTexture("plainbuilding/brack.bmp");
	//??
	plainBuildingMesh->loadTexture("plainbuilding/w2.bmp");
	//?/
	plainBuildingMesh->loadTexture("plainbuilding/store.bmp");
	//roof
	plainBuildingMesh->loadTexture("plainbuilding/top.bmp");
	//roof rim
	plainBuildingMesh->loadTexture("plainbuilding/top.bmp");
	//door 1
	plainBuildingMesh->loadTexture("plainbuilding/door.bmp");
	//door 2
	plainBuildingMesh->loadTexture("plainbuilding/door2.bmp");
	//ac
	plainBuildingMesh->loadTexture("plainbuilding/AC.bmp");
	//gutter pipe
	plainBuildingMesh->loadTexture("plainbuilding/iron.bmp");



	//Large Habitat Scene
	GameObject *habitat = new GameObject("test");
	habitat->setTranslation(glm::vec3(0.0f, -100.0f, 0.0f));
	habitat->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	habitat->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* habitatMesh = new MeshComponent("test");
	//testObject->addComponent(testMesh);
	habitatMesh->setRenderer(renderer);
	//testMesh->loadObject("habitat.obj");

	//benches	
	habitatMesh->loadTexture("tex/habitatWood.bmp");
	//buildings
	habitatMesh->loadTexture("tex/habitatBuilding2.bmp");
	//leaves
	habitatMesh->loadTexture("tex/habitatGrass.bmp");
	//lamps bulbs
	habitatMesh->loadTexture("tex/habitatBlack.bmp");
	//lamp posts
	habitatMesh->loadTexture("tex/habitatWeird.bmp");
	//paths/bridge
	habitatMesh->loadTexture("tex/habitatBuilding.bmp");
	//terrain
	habitatMesh->loadTexture("tex/habitatTerrain.bmp");
	//trees
	habitatMesh->loadTexture("tex/habitatWood2.bmp");
	//water
	habitatMesh->loadTexture("tex/habitatWater.bmp");
	//windows
	habitatMesh->loadTexture("tex/habitatWindow.bmp");

	*/