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

void IronRifts::pushState(AbstractState* newState)
{
	if (!states.empty()) {						// pause current state
		states.back()->Pause();
	}


	states.push_back(newState);					//store and init the new state
	states.back()->init();
}



void IronRifts::popState()
{
	if (!states.empty()) {						// cleanup the current state
		states.back()->Cleanup();
		states.pop_back();
	}


	if (!states.empty()) {						//resume previous state
		states.back()->Resume();
	}
}


void IronRifts::changeState(AbstractState* newState)
{
	if (!states.empty()) {						// cleanup the current state
		states.back()->Cleanup();
		states.pop_back();
	}


	states.push_back(newState);					// store and init the new state
	states.back()->init();
}


void IronRifts::cleanupStates()
{
	while (!states.empty()) {					// cleanup the all states
		states.back()->Cleanup();
		states.pop_back();
	}
}




