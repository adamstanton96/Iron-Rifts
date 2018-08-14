#pragma once
/*============================================================================ =
Iron Rifts (State Manager)

This class holds the possible states Iron Rifts could be in
============================================================================ =*/

#include "AbstractState.h"
#include <vector>
#include "InputSystem.h"

class AbstractState;
	
class IronRifts
{
public:
	IronRifts(){}

	void init();
	void update(double dt); //Check Input for a state change, possibly change state and then call update on the current state.

	void pushState(AbstractState*);
	void changeState(AbstractState* newState);

	void popState();
	void cleanupStates();


	///AbstractState* activeState;
	AbstractState* pauseState;
	AbstractState* playState;
	AbstractState* StartState;
	//InputSystem input;
private:
	

	std::vector<AbstractState*> states;
};
