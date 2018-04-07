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


//timer
#include <ctime>
#include <cstdlib>
#include "time.h"

// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
std::clock_t start;
double dt;


//Input System
InputSystem *inputSystem = new SDLInputSystem();

//physics system.
PhysicsSystem* collisionsystem = new IronRiftsPhysicsSystem();

//Audio System
IrrKlangAudioSystem * audioSystem = new IrrKlangAudioSystem("audioSystem");

//camera set up
Camera *cameraComponent = new Camera("camera");

//Render System
RenderingSystem* renderer = new openglRenderer();

//Temporarily hold all objects so that main isn't so awkward
std::vector<GameObject*> objectList;




void createWall(glm::vec3 pos, float rotation, float scale)
{
	//Wall Panel 1
	GameObject *wall = new GameObject("wall");
	wall->setPosition(glm::vec3(pos));
	wall->setScaling(glm::vec3(scale));
	wall->setRotationAxis(glm::vec3(0, 1, 0));
	wall->setRotationDegrees(rotation);

	RigidBodyComponent* wallBody = new RigidBodyComponent("Rigid Body");
	wall->addComponent(wallBody);
	wallBody->setCollisionSystem(collisionsystem);
	wallBody->setBodyType("STATIC");
	wallBody->setBoundingType("OBB");

	MeshComponent* wallMesh = new MeshComponent("test");
	wall->addComponent(wallMesh);
	wallMesh->setRenderer(renderer);
	wallMesh->loadObject("../../assets/cube_with_2UVs.DAE");
	wallMesh->loadTexture("../../assets/Scene/wall.bmp");

	objectList.push_back(wall);
}


void createGround(glm::vec3 pos)
{
		//Ground Plane
		GameObject *GroundPlane = new GameObject("Ground Plane");
		GroundPlane->setPosition(glm::vec3(pos));
		GroundPlane->setScaling(glm::vec3(10, 0.001, 10));
		GroundPlane->setRotationAxis(glm::vec3(NULL, NULL, NULL));
		RigidBodyComponent* rigidBody4 = new RigidBodyComponent("Rigid Body");
		GroundPlane->addComponent(rigidBody4);
		rigidBody4->setCollisionSystem(collisionsystem);
		rigidBody4->setBodyType("STATIC");
		MeshComponent* secondMesh = new MeshComponent("cube");
		GroundPlane->addComponent(secondMesh);
		secondMesh->setRenderer(renderer);
		secondMesh->loadObject("../../assets/cube_with_2UVs.DAE");
		secondMesh->loadTexture("../../assets/tex/scifiFloor.bmp");
		
		objectList.push_back(GroundPlane);
}



int main(int argc, char *argv[])
{
	
	inputSystem->init();
	audioSystem->init();

	cameraComponent->setEye(glm::vec3(0.0f, 2.0f, 0.0f));
	cameraComponent->setAt(glm::vec3(0.0f, 1.0f, -1.0f));
	cameraComponent->setUp(glm::vec3(0.0f, 1.0f, -1.0f));
	cameraComponent->setRotation(0.0f);
	cameraComponent->setInput(inputSystem);
	cameraComponent->init();

	renderer->camera = cameraComponent;

	////////////////////////////////////////////////////
	//First Object - Acting as player (camera component / movement component)
	GameObject *Player = new GameObject("player");
	Player->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
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
	int names[] = 
	{ 
		0,1,2,3,4,5,6,7,8,      //vertical corridor 0-8
		9,10,11,12,13,14,15,16,  //horizontal corridor 9-16

		17,18,19,20,21,22,23,24,	//vertical left corridor 17 -24

		25,26,27,28,29,30,31,32,	//vertical right corridor 25 - 32

		33,34,35,36,37,38,	//horizontal bottom corridor 33 - 38

		39,40,41,42,43,44	//horizontal bottom corridor 39 - 34
	
	
	};



	glm::vec2 locations[] = 
	{ 
		{ 0,0 },{ 0,-20 },{ 0,-40 },{ 0,-60 },{ 0,-80 },{ 0,-100 },{ 0,-120},{ 0,-140 },{ 0,-150 },					//vertical corridor 0-8  (9)

		{ -80,-75 },{ -60,-75 },{ -40,-75 },{ -20,-75 },{ 20,-75 },{ 40,-75 },{ 60,-75 },{ 80,-75 },				//horizontal corridor 9-16 (8)
	
		{ -80, 0 },{ -80,-20 },{ -80,-40 },{ -80,-60 },{ -80,-100 },{ -80,-120 },{ -80,-140 },{ -80,-150 },			//vertical left corridor 17-24 (8)

		{ 80, 0 },{ 80,-20 },{ 80,-40 },{ 80,-60 },{ 80,-100 },{ 80,-120 },{ 80,-140 },{ 80,-150 },				//vertical Right corridor 25-32 (8)

		{ -60, 5 },{ -40, 5 },{ -20, 5 },{ 20, 5 },{ 40, 5 },{ 60, 5 },		//horizontal bottom corridor 33 - 38 (6)

	   { -60, -150 },{ -40, -150 },{ -20, -150 },{ 20, -150 },{ 40, -150 },{ 60, -150 }		//horizontal top corridor 39 - 34(6)


	
	
	
	};
	std::pair<int, int> edges[] = 
	{ 
		path(0,1),path(1,2),path(2,3),path(3,4), path(4,5), path(5,6), path(6,7),path(7,8),				//vertical corridor

		path(4,12),path(12,11),path(11,10),path(10,9), path(4,13), path(13,14), path(14,15),path(15,16), //horicontal corridor

		path(17,18),path(18,19),path(19,20),path(20,9), path(9,21), path(21,22), path(22,23),path(23,24), //vertical left corridor

		path(25,26),path(26,27),path(27,28),path(28,16), path(16,29), path(29,30), path(30,31),path(31,32), //vertical right corridor

		path(0,35),path(35,34),path(34,33),path(33,17), path(0,36), path(36,37), path(37,38),path(38,25), //horizontal bottom corridor

		path(24,39),path(39,40),path(40,41),path(41,8), path(8,42), path(42,43), path(43,44),path(44,32) //horizontal top corridor
	};



	float weights[] = 
{   1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1
	
	};

	AISystem* AiSys = new AISystem();
	AstarGraph* graph = new AstarGraph(names, locations, edges, weights, 45, 48);

	AiSys->addPathGraph(graph);
	EnemyAI->setAIsystem(AiSys);
	EnemyAI->init();
	////////////////////////////////////////////////////
	//AI test object (enemy Player)
	//Green Demo Cube
	GameObject *Enemey = new GameObject("Enemy AI Cube");
	Enemey->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	Enemey->setScaling(glm::vec3(0.05, 0.05, 0.05));
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
	EnemeyMesh->loadObject("../../assets/duck_triangulate.DAE");
	EnemeyMesh->loadTexture("../../assets/tex/habitatWood2.bmp");

	objectList.push_back(Enemey);


	////////////////////////////////////////////////////
	//Scene/////////////////////////////////////////////


	//Start (0, 0)
	createGround(glm::vec3(0.0f, -5.0f, 0.0f));//0

	//Hub 1
	createGround(glm::vec3(-20.0f, -5.0f, 0.0f));//1
	createGround(glm::vec3(-40.0f, -5.0f, 0.0f));//2
	createGround(glm::vec3(-60.0f, -5.0f, 0.0f));//3
	createGround(glm::vec3(-60.0f, -5.0f, -20.0f));//6
	createGround(glm::vec3(-60.0f, -5.0f, -40.0f));//9
	createGround(glm::vec3(-40.0f, -5.0f, -20.0f));//5
	createGround(glm::vec3(-80.0f, -5.0f, -20.0f));//7
	createGround(glm::vec3(-80.0f, -5.0f, -40.0f));//10
	createGround(glm::vec3(-80.0f, -5.0f,  0.0f));//4
	createGround(glm::vec3(-40.0f, -5.0f, -40.0f));//8
	createGround(glm::vec3(-80.0f, -5.0f, -60.0f));//11

	

	//hub2
	createGround(glm::vec3(20.0f, -5.0f, 0.0f));//1
	createGround(glm::vec3(40.0f, -5.0f, 0.0f));//2
	createGround(glm::vec3(60.0f, -5.0f, 0.0f));//3
	createGround(glm::vec3(40.0f, -5.0f, -20.0f));//5
	createGround(glm::vec3(60.0f, -5.0f, -20.0f));//6
	createGround(glm::vec3(40.0f, -5.0f, -40.0f));//8
	createGround(glm::vec3(60.0f, -5.0f, -40.0f));//9

	createGround(glm::vec3(80.0f, -5.0f, -40.0f));//10
	createGround(glm::vec3(80.0f, -5.0f, -20.0f));//7
	createGround(glm::vec3(80.0f, -5.0f, 0.0f));//4
	createGround(glm::vec3(80.0f, -5.0f, -60.0f));//11



	//hub 3
	createGround(glm::vec3(-80.0f, -5.0f, -100.0f));//1
	createGround(glm::vec3(-80.0f, -5.0f, -120.0f));//2
	createGround(glm::vec3(-60.0f, -5.0f, -120.0f));//3
	createGround(glm::vec3(-40.0f, -5.0f, -120.0f));//4

	createGround(glm::vec3(-80.0f, -5.0f, -140.0f));//5
	createGround(glm::vec3(-60.0f, -5.0f, -140.0f));//6
	createGround(glm::vec3(-40.0f, -5.0f, -140.0f));//7

	createGround(glm::vec3(-80.0f, -5.0f, -160.0f));//8
	createGround(glm::vec3(-60.0f, -5.0f, -160.0f));//9
	createGround(glm::vec3(-40.0f, -5.0f, -160.0f));//10
	createGround(glm::vec3(-20.0f, -5.0f, -160.0f));//11

	//hub 4
	createGround(glm::vec3(80.0f, -5.0f, -100.0f));//1

	createGround(glm::vec3(80.0f, -5.0f, -120.0f));//2
	createGround(glm::vec3(60.0f, -5.0f, -120.0f));//3
	createGround(glm::vec3(40.0f, -5.0f, -120.0f));//4

	createGround(glm::vec3(80.0f, -5.0f, -140.0f));//5
	createGround(glm::vec3(60.0f, -5.0f, -140.0f));//6
	createGround(glm::vec3(40.0f, -5.0f, -140.0f));//7

	createGround(glm::vec3(80.0f, -5.0f, -160.0f));//8
	createGround(glm::vec3(60.0f, -5.0f, -160.0f));//9
	createGround(glm::vec3(40.0f, -5.0f, -160.0f));//10

	createGround(glm::vec3(20.0f, -5.0f, -160.0f));//10

	//Center and corridors
	//vertical
	createGround(glm::vec3(0.0f, -5.0f, -20.0f));//1
	createGround(glm::vec3(0.0f, -5.0f, -40.0f));//2
	createGround(glm::vec3(0.0f, -5.0f, -60.0f));//3
	createGround(glm::vec3(0.0f, -5.0f, -80.0f));//4
	createGround(glm::vec3(0.0f, -5.0f, -100.0f));//5
	createGround(glm::vec3(0.0f, -5.0f, -120.0f));//6
	createGround(glm::vec3(0.0f, -5.0f, -140.0f));//7
	createGround(glm::vec3(0.0f, -5.0f, -160.0f));//8

	//horizontal
	createGround(glm::vec3(-20.0f, -5.0f, -80.0f));//3
	createGround(glm::vec3(-40.0f, -5.0f, -80.0f));//2
	createGround(glm::vec3(-60.0f, -5.0f, -80.0f));//1
	createGround(glm::vec3(-80.0f, -5.0f, -80.0f));//0
	createGround(glm::vec3(20.0f, -5.0f, -80.0f));//5
	createGround(glm::vec3(40.0f, -5.0f, -80.0f));//6
	createGround(glm::vec3(60.0f, -5.0f, -80.0f));//7
	createGround(glm::vec3(80.0f, -5.0f, -80.0f));//8
	
	//center
	createGround(glm::vec3(-20.0f, -5.0f, -100.0f));//9
	createGround(glm::vec3(20.0f, -5.0f, -100.0f));//10
	createGround(glm::vec3(20.0f, -5.0f, -60.0f));//11
	createGround(glm::vec3(-20.0f, -5.0f, -60.0f));//12
	

	//walls hub 1/2					  
	createWall(glm::vec3(-60.0f, -5.0f, 20.0f), 0, 10);//3
	createWall(glm::vec3(-40.0f, -5.0f, 20.0f), 0, 10);//2
	createWall(glm::vec3(-20.0f, -5.0f, 20.0f), 0, 10);//1
	createWall(glm::vec3(0.0f, -5.0f, 20.0f), 0, 10);//0
	createWall(glm::vec3(20.0f, -5.0f, 20.0f), 0, 10);//1
	createWall(glm::vec3(40.0f, -5.0f, 20.0f), 0, 10);//2
	createWall(glm::vec3(60.0f, -5.0f, 20.0f), 0, 10);//3

	//walss hub 1/3
	createWall(glm::vec3(-100.0f, -5.0f, -20.0f), 0 , 10);//1
	createWall(glm::vec3(-100.0f, -5.0f, -40.0f), 0, 10);//2
	createWall(glm::vec3(-100.0f, -5.0f, -60.0f), 0, 10);//3
	createWall(glm::vec3(-100.0f, -5.0f, -80.0f), 0, 10);//4
	createWall(glm::vec3(-100.0f, -5.0f, -100.0f), 0, 10);//5
	createWall(glm::vec3(-100.0f, -5.0f, -120.0f), 0, 10);//6
	createWall(glm::vec3(-100.0f, -5.0f, -140.0f), 0, 10);//7

	//wall hub2/4													 
	createWall(glm::vec3(100.0f, -5.0f, -20.0f), 0, 10);//1
	createWall(glm::vec3(100.0f, -5.0f, -40.0f), 0, 10);//2
	createWall(glm::vec3(100.0f, -5.0f, -60.0f), 0, 10);//3
	createWall(glm::vec3(100.0f, -5.0f, -80.0f), 0, 10);//4
	createWall(glm::vec3(100.0f, -5.0f, -100.0f), 0, 10);//5
	createWall(glm::vec3(100.0f, -5.0f, -120.0f), 0, 10);//6
	createWall(glm::vec3(100.0f, -5.0f, -140.0f), 0, 10);//7

	//walls hub 3/2					  
	createWall(glm::vec3(-60.0f, -5.0f, -180.0f), 0, 10);//3
	createWall(glm::vec3(-40.0f, -5.0f, -180.0f), 0, 10);//2
	createWall(glm::vec3(-20.0f, -5.0f, -180.0f), 0, 10);//1
	createWall(glm::vec3(0.0f, -5.0f, -180.0f), 0, 10);//0
	createWall(glm::vec3(20.0f, -5.0f, -180.0f), 0, 10);//1
	createWall(glm::vec3(40.0f, -5.0f, -180.0f), 0, 10);//2
	createWall(glm::vec3(60.0f, -5.0f, -180.0f), 0, 10);//3

	//rest of the walls
	//bottom left
	createWall(glm::vec3(-20.0f, -5.0f, -20.0f), 0, 10);
	createWall(glm::vec3(-20.0f, -5.0f, -40.0f), 0, 10);
	createWall(glm::vec3(-40.0f, -5.0f, -60.0f), 0, 10);
	createWall(glm::vec3(-60.0f, -5.0f, -60.0f), 0, 10);

	//bottom Right
	createWall(glm::vec3(20.0f, -5.0f, -20.0f), 0, 10);
	createWall(glm::vec3(20.0f, -5.0f, -40.0f), 0, 10);
	createWall(glm::vec3(40.0f, -5.0f, -60.0f), 0, 10);
	createWall(glm::vec3(60.0f, -5.0f, -60.0f), 0, 10);

	//top left
	createWall(glm::vec3(-60.0f, -5.0f, -100.0f), 0, 10);
	createWall(glm::vec3(-40.0f, -5.0f, -100.0f), 0, 10);
	createWall(glm::vec3(-20.0f, -5.0f, -120.0f), 0, 10);
	createWall(glm::vec3(-20.0f, -5.0f, -140.0f), 0, 10);

	//top Right
	createWall(glm::vec3(60.0f, -5.0f, -100.0f), 0, 10);
	createWall(glm::vec3(40.0f, -5.0f, -100.0f), 0, 10);
	createWall(glm::vec3(20.0f, -5.0f, -120.0f), 0, 10);
	createWall(glm::vec3(20.0f, -5.0f, -140.0f), 0, 10);

	
	
	
	int frameRate = 0;
	float timeSoFar = 0;
	bool running = true;

	SDL_Event sdlEvent;
	do
	{
		frameRate++;
		timeSoFar += dt;
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
			objectList[i]->update(dt);
		}

		renderer->swapBuffers();


 
		//Stores the time past the frame has taken to complete
		dt = (std::clock() - start) / (double)CLOCKS_PER_SEC;


		//Show frame rate
		if (timeSoFar >= 1)
		{
			cout << frameRate << endl;

			timeSoFar = 0;
			frameRate = 0;
		}


	
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