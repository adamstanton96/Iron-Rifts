#pragma once
#include "AbstractState.h"
#include <vector>

class IronRifts
{
public:
	IronRifts(){}

	void update(double dt); //Check Input for a state change, possibly change state and then call update on the current state.

	void addState(AbstractState*);

private:
	AbstractState* activeState;
	std::vector<AbstractState*> states;
};
