#pragma once
/*============================================================================ =
Iron Rifts (State Manager)

This class holds the possible 
============================================================================ =*/



#include "AbstractState.h"
#include <vector>
#include "InputSystem.h"

class IronRifts
{
public:
	IronRifts(){}

	void update(double dt); //Check Input for a state change, possibly change state and then call update on the current state.

	void addState(AbstractState*);


	AbstractState* activeState;
	InputSystem* input;
private:


	std::vector<AbstractState*> states;
};
