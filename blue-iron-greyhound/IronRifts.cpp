#include "IronRifts.h"

void IronRifts::update(double dt)
{
	//Poll Inputs
	///
	

	//Check Inputs for a State Change
	///
	

	//Update ActiveState
	activeState->update(dt);

}

void IronRifts::addState(AbstractState* newState)
{
	states.push_back(newState);
}




