#pragma once
#include "System.h"
#include "SDLInputSystem.h"

class AbstractState : public System
{
public:

	///virtual ~AbstractState() = 0;

	virtual void init() = 0;
	virtual void update(double dt) = 0;

	virtual void Cleanup() = 0;
	virtual void Resume() = 0;
	virtual void Pause() = 0;


	bool isPaused;
	SDLInputSystem inputs;
private:
};
