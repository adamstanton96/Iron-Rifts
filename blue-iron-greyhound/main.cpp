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

	//Creates Play state
	InfiniteDeathmatchState* playState = new InfiniteDeathmatchState(Level1.sceneObjects, Level1.objectList);
	

	//Menu State
	GameObject* inGameMenu = new GameObject("Ingamemenu");
	MenuUI* pauseMenu = new MenuUI(glm::vec3(0.0, 0.0f, -1.0f), glm::vec3(1.0, 0.5, 0.0001), "../../assets/tex/PausedMenu.png");
	inGameMenu->addComponent(pauseMenu);

	InGameMenuState* gameMenuState = new InGameMenuState(inGameMenu);



	//Game Manager
	IronRifts game;
	///game.activeState = playState;
	game.pauseState = gameMenuState;

	game.pushState(playState);



	//after adding states call init
	game.init();

	
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

