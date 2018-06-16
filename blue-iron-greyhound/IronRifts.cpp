#include "IronRifts.h"

void IronRifts::update(double dt)
{
	//Poll Inputs
	///

	//Check Inputs for a State Change
	///

	//Update ActiveState
	for (int i = 0; i < states.size(); i++)
		states[i]->update(dt);


}

void IronRifts::addState(AbstractState* newState)
{
	states.push_back(newState);
}