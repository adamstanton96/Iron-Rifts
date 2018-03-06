#pragma once
#include "Component.h"
#include "InputSystem.h"
#include <iostream>
#include "CollisionSystem.h"


class Raycast : public Component
{
public:
	Raycast(InputSystem *input, CollisionSystem* collisionSys)
	{
		this->input = input;
		this->collisionSys = collisionSys;
	}

	~Raycast(){}


	void update() 
	{
		

		glm::vec3 playerForward(0, 0,-50);  //ray direction 

		//Collisions are using the position of the player and that position plus the direction about to make a line
		GameObject* obj = collisionSys->rayCollisionCheck(playerForward, getUser()->getPosition());

		//if a collision was found and its not the players cube
		if (obj != nullptr)
			if (obj != getUser())
			cout << "ray collision	-	" << obj->getName() << endl;

			
	}

	void init()
	{

	}

private:
	InputSystem *input;
	CollisionSystem* collisionSys;

	glm::vec2 ray;
};