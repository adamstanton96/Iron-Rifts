/*=============================================================================
* AudioSystem.h
* Author: Adam Stanton
* Abstract parent to any audio system classes...
=============================================================================*/

#pragma once
#include "System.h"

class AudioSystem : public System
{
public:

	AudioSystem() {};
	virtual ~AudioSystem() {};

	virtual void init() = 0;

};