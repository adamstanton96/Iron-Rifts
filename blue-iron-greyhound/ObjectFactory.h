/*=============================================================================
* ObjectFactory.h
* Author: Adam Stanton
* Used to create objects...
=============================================================================*/

#pragma once
#include "InputSystem.h"
#include "GameObject.h"
#include <SDL.h>
#include <string>
#include <map>
#include <iostream>

typedef std::pair<std::string, GameObject*> objects;

class ObjectFactory
{
public:
	ObjectFactory();
	virtual ~ObjectFactory();

	void init();
	GameObject* createObject(std::string input, glm::vec3 position, float rotation);

private:
	void initSystems();
	void initObjects();
	std::map<std::string, GameObject*> objectMap;
};