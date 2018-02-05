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
	void addSystem(System *system);
	GameObject* createObject(std::string input, glm::vec3 position, float rotation);

private:
	void initSystems();
	void initObjects();

	template<class T>
	T *getSystem();

	std::vector<System *> systemList;
	std::map<std::string, GameObject*> objectMap;
};

template<class T>
T *ObjectFactory::getSystem()
{
	bool found = false;
	T *system = nullptr;
	int i = 0;

	while (!found) {

		//Checks if we have found Component
		if (system = dynamic_cast<T*>(componentList[i]))
			found = true;

		i++;
		//Reached the end
		if (i == componentList.size())
			found = true;
	}
	return system;
}