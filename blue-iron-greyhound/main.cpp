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
#include "IrrKlangAudioSystem.h"


#include "RigidBodyComponent.h"
#include "CollisionSystem.h"

#include "AudioTestComponent.h"
//temp
///
//#include "OBB.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
///

//timer
#include <ctime>
#include <cstdlib>
#include "time.h"


// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
std::clock_t start;
double dt = 0;




int main(int argc, char *argv[])
{
	//Input System
	InputSystem *inputSystem = new SDLInputSystem();
	inputSystem->init();

	//New collision System
	CollisionSystem* collisionsystem = new CollisionSystem();

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

	//render set up
	RenderingSystem* renderer = new openglRenderer();
	renderer->camera = cameraComponent;

	//Temporarily hold all objects so that main isn't so awkward
	std::vector<GameObject*> objectList;
	

	//First Object - Acting as player (camera component / movement component)
	GameObject *Player = new GameObject("player");
	Player->setPosition(glm::vec3(5.0f, 0.0f, 90.0f));
	Player->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	Player->setRotationAxis(glm::vec3(0, -1, 0));
	Player->setRotationDegrees(0);


	RigidBodyComponent* rigidBody = new RigidBodyComponent("Rigid Body");
	Player->addComponent(rigidBody);
	rigidBody->setCollisionSystem(collisionsystem);
	rigidBody->setBodyType("DYNAMIC");
	rigidBody->setBoundingType("OBB");
	
	MeshComponent* meshComponent = new MeshComponent("sphere");
	Player->addComponent(meshComponent);
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("../../assets/blenderTest.dae");
	meshComponent->loadTexture("../../assets/tex/scifiFloor.bmp");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);


	AudioTester *audioTester = new AudioTester("audioTester");
	audioTester->setAudio(audioSystem);
	audioTester->setInput(inputSystem);

	Player->addComponent(audioTester);
	Player->addComponent(cameraComponent);
	Player->addComponent(moveComponent);

	objectList.push_back(Player);

	

	//Animated Object
	GameObject *barrier2 = new GameObject("old building");
	barrier2->setPosition(glm::vec3(0.0f, 0.0f,60.0f));
	barrier2->setScaling(glm::vec3(1, 1, 1));
	barrier2->setRotationAxis(glm::vec3(0, 1, 0));
	barrier2->setRotationDegrees(0);


	RigidBodyComponent* rigidBody3 = new RigidBodyComponent("Rigid Body");
	barrier2->addComponent(rigidBody3);
	rigidBody3->setCollisionSystem(collisionsystem);
	rigidBody3->setBodyType("STATIC");
	rigidBody3->setBoundingType("OBB");

	AnimatedMeshComponent* barriermesh2 = new AnimatedMeshComponent("test");
	barrier2->addComponent(barriermesh2);
	barriermesh2->setRenderer(renderer);
	//barriermesh2->loadObject("../../assets/Monster_1/Monster_1.dae");
	barriermesh2->loadObject("../../assets/A_Test_Guy.dae");
	//barriermesh2->loadObject("../../assets/Monster_1/A_Test.dae");
	//barriermesh2->loadObject("../../assets/Monster_1/A_Test_Soldier.dae");
	//barriermesh2->loadObject("../../assets/RobotAnimated.dae");

	barriermesh2->loadTexture("../../assets/scifi.bmp");

	objectList.push_back(barrier2);


	//Ground Plane
	GameObject *GroundPlane = new GameObject("Collada");
	GroundPlane->setPosition(glm::vec3(0.0f, -5.0f, -60.0f));
	GroundPlane->setScaling(glm::vec3(60, 0.1f, 60));

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

	//Second Ground Plane 
	GameObject *GroundPlane2 = new GameObject("Collada");
	GroundPlane2->setPosition(glm::vec3(0.0f, -5.0f, 60.0f));
	GroundPlane2->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane2->setRotationAxis(glm::vec3(NULL, NULL, NULL));
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

			//Give delta time to the test animation mesh (it is needed inside its skeleton objet)
			barriermesh2->setSkeletonDeltaTime(dt);




	
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