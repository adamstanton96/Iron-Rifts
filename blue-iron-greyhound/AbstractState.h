#pragma once
#include "System.h"
#include "SDLInputSystem.h"
#include "IronRifts.h"

class IronRifts;

class AbstractState : public System
{
public:

	virtual void init() = 0;
	virtual void update(double dt, IronRifts* game) = 0;

	virtual void Cleanup() = 0;
	virtual void Resume() = 0;
	virtual void Pause() = 0;


	bool isPaused;
	SDLInputSystem inputs;

	double inputTimer;
	double inputTimerThreshold;
private:
};
