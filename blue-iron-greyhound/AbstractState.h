#pragma once
#include "System.h"
#include "SDLInputSystem.h"
#include "IronRifts.h"

class IronRifts;

class AbstractState : public System
{
public:

	///virtual ~AbstractState() = 0;

	virtual void init() = 0;
	virtual void update(double dt, IronRifts* game) = 0;

	virtual void Cleanup() = 0;
	virtual void Resume() = 0;
	virtual void Pause() = 0;


	bool isPaused;
	SDLInputSystem inputs;

	double timer;
	double timeThreshold;
private:
};
