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


#include "OpenglRenderer.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "MovementComponent.h"
#include "SDLInputSystem.h"
#include "AnimatedMeshComponent.h"


#include "RigidBodyComponent.h"
#include "CollisionSystem.h"

//temp
///
#include "OBB.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
///

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
	//camera set up

	Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 10.0f, 30.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0);

	//Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 2.0f, 30.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), 0.0);

	cameraComponent->init();

	//render set up
	RenderingSystem* renderer = new openglRenderer();
	renderer->camera = cameraComponent;

	//Input System
	InputSystem *inputSystem = new SDLInputSystem();
	inputSystem->init();

	//New collision System
	CollisionSystem* collisionsystem = new CollisionSystem();

	//Temporarily hold all objects so that main isn't so awkward
	std::vector<GameObject*> objectList;
	

	//First Object - Acting as player (camera component / movement component)
	GameObject *Player = new GameObject("player");
	Player->setTranslation(glm::vec3(5.0f, 0.0f, 60.0f));
	Player->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	Player->setCameraRotation(0.0);
	Player->setRenderRotateVec(glm::vec3(0, -1, 0));
	Player->setRenderRotateDeg(0);


	RigidBodyComponent* rigidBody = new RigidBodyComponent("Rigid Body");
	Player->addComponent(rigidBody);
	rigidBody->setCollisionSystem(collisionsystem);
	rigidBody->setBodyType("DYNAMIC");
	rigidBody->setBoundingType("OBB");
	
	MeshComponent* meshComponent = new MeshComponent("sphere");
	Player->addComponent(meshComponent);
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("../../assets/AlienPlanet2.dae");
	meshComponent->loadTexture("../../assets/tex/scifiFloor.bmp");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);

	Player->addComponent(cameraComponent);
	Player->addComponent(moveComponent);

	objectList.push_back(Player);

	////////////////////////////////////////////////////

	//spider robot for animation tests
	GameObject *barrier2 = new GameObject("old building");
	barrier2->setTranslation(glm::vec3(20.0f, 0.0f, 90.0f));
	barrier2->setScaling(glm::vec3(4, 4, 4));
	barrier2->setRenderRotateVec(glm::vec3(1, 0, 0));
	barrier2->setRenderRotateDeg(-90);

	RigidBodyComponent* rigidBody3 = new RigidBodyComponent("Rigid Body");
	barrier2->addComponent(rigidBody3);
	rigidBody3->setCollisionSystem(collisionsystem);
	rigidBody3->setBodyType("STATIC");
	rigidBody3->setBoundingType("OBB");

	AnimatedMeshComponent* barriermesh2 = new AnimatedMeshComponent("test");
	barrier2->addComponent(barriermesh2);
	barriermesh2->setRenderer(renderer);
	//barriermesh2->toggleAnimationAbilities();
	barriermesh2->loadObject("../../assets/RobotAnimated.dae");
	barriermesh2->loadTexture("../../assets/RobotAnimated.bmp");

	objectList.push_back(barrier2);
	///////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////

	//road barrier 1
	GameObject *barrier = new GameObject("old building");
	barrier->setTranslation(glm::vec3(-20.0f, 0.0f, 90.0f));
	barrier->setScaling(glm::vec3(3, 3, 3));
	barrier->setRenderRotateVec(glm::vec3(1, 0, 0));
	barrier->setRenderRotateDeg(-90);

	RigidBodyComponent* rigidBody2 = new RigidBodyComponent("Rigid Body");
	barrier->addComponent(rigidBody2);
	rigidBody2->setCollisionSystem(collisionsystem);
	rigidBody2->setBodyType("STATIC");
	rigidBody2->setBoundingType("OBB");

	MeshComponent* barriermesh = new MeshComponent("test");
	//AnimatedMeshComponent* barriermesh = new AnimatedMeshComponent("test");
	barrier->addComponent(barriermesh);
	//barriermesh->toggleAnimationAbilities();
	barriermesh->setRenderer(renderer);
	barriermesh->loadObject("../../assets/Warbot-Blue.dae");
	barriermesh->loadTexture("../../assets/tex/scifi.bmp");

	objectList.push_back(barrier);

	///////////////////////////////////////////////////////////////////


	//Ground Plane
	GameObject *GroundPlane = new GameObject("Collada");
	GroundPlane->setTranslation(glm::vec3(0.0f, -5.0f, -30.0f));
	GroundPlane->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane->setRenderRotateVec(glm::vec3(0, 0, 0));
	RigidBodyComponent* rigidBody4 = new RigidBodyComponent("Rigid Body");
	GroundPlane->addComponent(rigidBody4);
	rigidBody4->setCollisionSystem(collisionsystem);
	rigidBody4->setBodyType("STATIC");
	MeshComponent* secondMesh = new MeshComponent("cube");
	GroundPlane->addComponent(secondMesh);
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("../../assets/cube_with_2UVs.dae");
	secondMesh->loadTexture("../../assets/tex/rockyground.bmp");
	
	objectList.push_back(GroundPlane);

	//Ground Plane 2
	GameObject *GroundPlane2 = new GameObject("Collada");
	GroundPlane2->setTranslation(glm::vec3(0.0f, -5.0f, 50.0f));
	GroundPlane2->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	RigidBodyComponent* rigidBody5 = new RigidBodyComponent("Rigid Body");
	GroundPlane2->addComponent(rigidBody5);
	rigidBody5->setCollisionSystem(collisionsystem);
	rigidBody5->setBodyType("STATIC");
	MeshComponent* secondMesh2 = new MeshComponent("cube");
	GroundPlane2->addComponent(secondMesh2);
	secondMesh2->setRenderer(renderer);
	secondMesh2->loadObject("../../assets/cube_with_2UVs.DAE");
	secondMesh2->loadTexture("../../assets/tex/rockyground.bmp");

	objectList.push_back(GroundPlane2);

	//Wall 1
	GameObject *walls = new GameObject("Collada");
	walls->setTranslation(glm::vec3(0.0f, 10.0f, -25.0f));
	walls->setScaling(glm::vec3(60, 0.5f, 60));
	walls->setRenderRotateVec(glm::vec3(1, 0, 0));
	walls->setRenderRotateDeg(90);
	RigidBodyComponent* rigidBody6 = new RigidBodyComponent("Rigid Body");
	walls->addComponent(rigidBody6);
	rigidBody6->setCollisionSystem(collisionsystem);
	rigidBody6->setBodyType("STATIC");
	MeshComponent* wallmesh = new MeshComponent("cube");
	walls->addComponent(wallmesh);
	wallmesh->setRenderer(renderer);
	wallmesh->loadObject("../../assets/cube_with_2UVs.DAE");
	wallmesh->loadTexture("../../assets/tex/scifi.bmp");

	objectList.push_back(walls);
	
	//Wall 2
	GameObject *walls2 = new GameObject("Collada");
	walls2->setTranslation(glm::vec3(-60.0f, -50.0f, -25.0f));
	walls2->setScaling(glm::vec3(0.5f, 60, 60));
	walls2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	RigidBodyComponent* rigidBody7 = new RigidBodyComponent("Rigid Body");
	walls2->addComponent(rigidBody7);
	rigidBody7->setCollisionSystem(collisionsystem);
	rigidBody7->setBodyType("STATIC");
	MeshComponent* wallmesh2 = new MeshComponent("cube");
	walls2->addComponent(wallmesh2);
	wallmesh2->setRenderer(renderer);
	wallmesh2->loadObject("../../assets/cube_with_2UVs.DAE");
	wallmesh2->loadTexture("../../assets/tex/scifi.bmp");

	objectList.push_back(walls2);

	//Wall 2
	GameObject *walls3 = new GameObject("Collada");
	walls3->setTranslation(glm::vec3(60.0f, -50.0f, -25.0f));
	walls3->setScaling(glm::vec3(0.5f, 60, 60));
	walls3->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	RigidBodyComponent* rigidBody8 = new RigidBodyComponent("Rigid Body");
	walls3->addComponent(rigidBody8);
	rigidBody8->setCollisionSystem(collisionsystem);
	rigidBody8->setBodyType("STATIC");
	MeshComponent* wallmesh3 = new MeshComponent("cube");
	walls3->addComponent(wallmesh3);
	wallmesh3->setRenderer(renderer);
	wallmesh3->loadObject("../../assets/cube_with_2UVs.DAE");
	wallmesh3->loadTexture("../../assets/tex/scifi.bmp");

	objectList.push_back(walls3);
	
	// Wall 4
	GameObject *walls4 = new GameObject("Collada");
	walls4->setTranslation(glm::vec3(60.0f, -50.0f, 80.0f));
	walls4->setScaling(glm::vec3(0.5f, 60, 60));
	walls4->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	RigidBodyComponent* rigidBody9 = new RigidBodyComponent("Rigid Body");
	walls4->addComponent(rigidBody9);
	rigidBody9->setCollisionSystem(collisionsystem);
	rigidBody9->setBodyType("STATIC");
	MeshComponent* wallmesh4 = new MeshComponent("cube");
	walls4->addComponent(wallmesh4);
	wallmesh4->setRenderer(renderer);
	wallmesh4->loadObject("../../assets/cube_with_2UVs.DAE");
	wallmesh4->loadTexture("../../assets/tex/scifi.bmp");

	objectList.push_back(walls4);
	
	//Wall 5
	GameObject *walls5 = new GameObject("Collada");
	walls5->setTranslation(glm::vec3(-60.0f, -50.0f, 80.0f));
	walls5->setScaling(glm::vec3(0.5f, 60, 60));
	walls5->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh5 = new MeshComponent("cube");
	walls5->addComponent(wallmesh5);
	wallmesh5->setRenderer(renderer);
	wallmesh5->loadObject("../../assets/cube_with_2UVs.DAE");
	wallmesh5->loadTexture("../../assets/tex/scifi.bmp");

	objectList.push_back(walls5);

	//Wall 6
	GameObject *walls6 = new GameObject("Collada");
	walls6->setTranslation(glm::vec3(0.0f, 10.0f, 170.0f));
	walls6->setScaling(glm::vec3(60, 0.5f, 60));
	walls6->setRenderRotateVec(glm::vec3(1, 0, 0));
	walls6->setRenderRotateDeg(90);
	MeshComponent* wallmesh6 = new MeshComponent("cube");
	walls6->addComponent(wallmesh6);
	wallmesh6->setRenderer(renderer);
	wallmesh6->loadObject("../../assets/cube_with_2UVs.DAE");
	wallmesh6->loadTexture("../../assets/tex/scifi.bmp");
	
	objectList.push_back(walls6);
	

	//Research Building Object
	GameObject *buildingObject = new GameObject("old building");
	buildingObject->setTranslation(glm::vec3(-5.0f, -5.0f, 0.0f));
	buildingObject->setScaling(glm::vec3(3.0f, 3.0f, 3.0f));
	buildingObject->setRenderRotateVec(glm::vec3(-1.0f, 0.0f, 0.0f));
	buildingObject->setRenderRotateDeg(90);
	RigidBodyComponent* rigidBodybuilding = new RigidBodyComponent("Rigid Body");
	buildingObject->addComponent(rigidBodybuilding);
	rigidBodybuilding->setCollisionSystem(collisionsystem);
	rigidBodybuilding->setBodyType("STATIC");
	rigidBodybuilding->setBoundingType("OBB");
	MeshComponent* buildingMesh = new MeshComponent("test");
	buildingObject->addComponent(buildingMesh);
	buildingMesh->setRenderer(renderer);
	buildingMesh->loadObject("../../assets/building.dae");
	

	buildingMesh->loadTexture("../../assets/tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("../../assets/tex/tubes.bmp");
	buildingMesh->loadTexture("../../assets/tex/building1.bmp");
	buildingMesh->loadTexture("../../assets/tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("../../assets/tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("../../assets/tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("../../assets/tex/sandstoneWall2.bmp");
	buildingMesh->loadTexture("../../assets/tex/sandstoneWall2.bmp");
	buildingMesh->loadTexture("../../assets/tex/tubes.bmp");
	buildingMesh->loadTexture("../../assets/tex/tubes.bmp");
	buildingMesh->loadTexture("../../assets/tex/fan1.bmp");
	buildingMesh->loadTexture("../../assets/tex/satDish.bmp");
	buildingMesh->loadTexture("../../assets/tex/building1.bmp");
	buildingMesh->loadTexture("../../assets/tex/tubes.bmp");

	objectList.push_back(buildingObject);


	//watchtower
	GameObject *watchTower = new GameObject("watch tower");
	watchTower->setTranslation(glm::vec3(-40.0f, -5.0f, 70.0f));
	watchTower->setScaling(glm::vec3(4.0f, 4.0f, 4.0f));
	watchTower->setRenderRotateVec(glm::vec3(-1, 0, 0));
	watchTower->setRenderRotateDeg(90);
	RigidBodyComponent* rigidBody1 = new RigidBodyComponent("Rigid Body");
	watchTower->addComponent(rigidBody1);
	rigidBody1->setCollisionSystem(collisionsystem);
	rigidBody1->setBodyType("STATIC");
	rigidBody1->setBoundingType("OBB");
	MeshComponent* watchTowerMesh = new MeshComponent("test");
	watchTower->addComponent(watchTowerMesh);
	watchTowerMesh->setRenderer(renderer);
	watchTowerMesh->loadTexture("../../assets/plainbuilding/iron.bmp");
	watchTowerMesh->loadObject("../../assets/watchtower.dae");
	
	objectList.push_back(watchTower);

	//TRASH PILE
	GameObject *trashPile = new GameObject("old building");
	trashPile->setTranslation(glm::vec3(40.0f, -5.0f, 30.0f));
	trashPile->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	trashPile->setRenderRotateVec(glm::vec3(0, 0, 0));
	trashPile->setRenderRotateDeg(90);
	RigidBodyComponent* rigidBody10 = new RigidBodyComponent("Rigid Body");
	trashPile->addComponent(rigidBody10);
	rigidBody10->setCollisionSystem(collisionsystem);
	rigidBody10->setBodyType("STATIC");
	MeshComponent* trashmesh = new MeshComponent("test");
	trashPile->addComponent(trashmesh);
	trashmesh->setRenderer(renderer);
	trashmesh->loadObject("../../assets/item01.obj");
	
	trashmesh->loadTexture("../../assets/Trash/damagedwood.bmp");
	trashmesh->loadTexture("../../assets/Trash/mossyConcrete.bmp");
	trashmesh->loadTexture("../../assets/Trash/scratchedblue.bmp");
	trashmesh->loadTexture("../../assets/Trash/stone.bmp");
	trashmesh->loadTexture("../../assets/Trash/scratchedmetal.bmp");
	trashmesh->loadTexture("../../assets/Trash/rustmetal.bmp");
	
	objectList.push_back(trashPile);

	////road barrier 1
	//GameObject *barrier = new GameObject("old building");
	//barrier->setTranslation(glm::vec3(-20.0f, -5.0f, 90.0f));
	//barrier->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	//barrier->setRenderRotateVec(glm::vec3(NULL, -NULL, NULL));
	//RigidBodyComponent* rigidBody2 = new RigidBodyComponent("Rigid Body");
	//barrier->addComponent(rigidBody2);
	//rigidBody2->setCollisionSystem(collisionsystem);
	//rigidBody2->setBodyType("STATIC");
	//MeshComponent* barriermesh = new MeshComponent("test");
	//barrier->addComponent(barriermesh);
	//barriermesh->setRenderer(renderer);
	//barriermesh->loadObject("../../assets/BARRIERE.obj");
	//barriermesh->loadTexture("../../assets/roadbarrier/BARRIERE.bmp");
	//
	//objectList.push_back(barrier);

	//road barrier 2
	/*GameObject *barrier2 = new GameObject("old building");
	barrier2->setTranslation(glm::vec3(0.0f, -5.0f, 90.0f));
	barrier2->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	barrier2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	RigidBodyComponent* rigidBody3 = new RigidBodyComponent("Rigid Body");
	barrier2->addComponent(rigidBody3);
	rigidBody3->setCollisionSystem(collisionsystem);
	rigidBody3->setBodyType("STATIC");
	MeshComponent* barriermesh2 = new MeshComponent("test");
	barrier2->addComponent(barriermesh2);
	barriermesh2->setRenderer(renderer);
	barriermesh2->loadObject("../../assets/BARRIERE.obj");
	barriermesh2->loadTexture("../../assets/roadbarrier/BARRIERE.bmp");

	objectList.push_back(barrier2);
*/

	//planet in the sky


	//GameObject *AlienPlanet = new GameObject("old building");
	//AlienPlanet->setTranslation(glm::vec3(-200, 200, -300));
	//AlienPlanet->setScaling(glm::vec3(50, 50, 50));
	//AlienPlanet->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	//MeshComponent* AlienPlanetMesh = new MeshComponent("test");
	//AlienPlanet->addComponent(AlienPlanetMesh);
	//AlienPlanetMesh->setRenderer(renderer);
	//AlienPlanetMesh->loadObject("../../assets/AlienPlanet2.dae");
	//AlienPlanetMesh->loadTexture("../../assets/tex/AlienPlanet.bmp");

	//objectList.push_back(AlienPlanet);

	////Not showing needs a change of texture
	//GameObject *AlienPlanet2 = new GameObject("old building");
	//AlienPlanet2->setTranslation(glm::vec3(200, 200, -300));
	//AlienPlanet2->setScaling(glm::vec3(50, 50, 50));
	//AlienPlanet2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	//MeshComponent* AlienPlanetMesh2= new MeshComponent("test");
	//AlienPlanet2->addComponent(AlienPlanetMesh2);
	//AlienPlanetMesh2->setRenderer(renderer);
	//AlienPlanetMesh2->loadObject("../../assets/AlienPlanet2.dae");
	//AlienPlanetMesh2->loadTexture("../../assets/tex/mercury.bmp");


	//objectList.push_back(AlienPlanet2);

	
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
	
		//Get Inputs - Temporary for free roam camera
		Player->input(dt);

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