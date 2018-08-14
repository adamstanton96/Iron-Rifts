/*=============================================================================
* Project: Blue Iron Greyhound
* Chloe Madden, Adam Stanton,  Paul McLaughlin, Thomas Mackrell.
=============================================================================*/

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

//Asset pathway:
/// ../../assets/
#include "SDL.h"

#include <glm/glm.hpp>

//timer
#include <ctime>
#include <cstdlib>
#include "time.h"

#include "InfiniteDeathmatchState.h"
#include "IronRifts.h"
#include "FirstLevel.h"

#include "GameObject.h"

#include "MenuUI.h"
#include "InGameMenuState.h"
#include "MainMenuState.h"



// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
std::clock_t start;
double dt;


int main(int argc, char *argv[])
{
	FirstLevel Level1;
	Level1.init();
	Level1.setup();
	Level1.loadPlayers();
	Level1.loadMap();

	////HUD/////////
	///HudLogic* healthLogic2 = new HUD_Health();
	///HudComponent* HelathBar2 = new HudComponent(glm::vec3(-0.5, 0.5f, -1.0f), glm::vec3(0.2, 0.03, 0.0001), healthLogic2);
	///Player->addComponent(HelathBar2);
	//////////////
	

	//in game Menu State
	GameObject* pauseObject = new GameObject("In-game Menu");
	MenuUI* pauseMenu = new MenuUI(glm::vec3(0.0, 0.0f, -1.0f), glm::vec3(1.0, 0.5, 0.0001), "../../assets/tex/PausedMenu.png");
	pauseObject->addComponent(pauseMenu);
	InGameMenuState* gameMenuState = new InGameMenuState(pauseObject);



	//Creates Play state
	InfiniteDeathmatchState* playState = new InfiniteDeathmatchState(Level1.sceneObjects, Level1.objectList);

	//Menu State
	GameObject* startMenu = new GameObject("Start Menu");
	MenuUI* startMenuUI = new MenuUI(glm::vec3(0.0, 0.0f, -1.0f), glm::vec3(1.0, 0.5, 0.0001), "../../assets/tex/MainMenuIronRifts.png");
	startMenu->addComponent(startMenuUI);
	MainMenuState* startMenuState = new MainMenuState(startMenu);

	//playState->init();


	//Game Manager
	IronRifts game;
	
	game.playState = playState;
	game.pauseState = gameMenuState;


	game.pushState(startMenuState);



	//after adding states call init
	///game.init();
	

	
	int frameRate = 0;
	float timeSoFar = 0;
	bool running = true;


	RenderingSystem* renderer = Level1.renderer;

	SDL_Event sdlEvent;

	do
	{
		frameRate++;
		timeSoFar += dt;
		start = std::clock();

		while (SDL_PollEvent(&sdlEvent)) 
		{

		}

		
		renderer->clearScreen();

		game.update(dt);

		renderer->swapBuffers();


		//Stores the time past the frame has taken to complete
		dt = (std::clock() - start) / (double)CLOCKS_PER_SEC;



	
	} while (running);


	return 0;
}

