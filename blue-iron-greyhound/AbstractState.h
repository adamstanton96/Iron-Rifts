#pragma once
#include "System.h"

class AbstractState : public System
{
public:

	///virtual ~AbstractState() = 0;

	virtual void init() = 0;
	virtual void update(double dt) = 0;

private:

};
