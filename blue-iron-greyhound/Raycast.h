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


	void init()
	{
		
	}

	void update() 
	{
		this->rayDirection = glm::vec3(0, 0, -1);
		this->rayMagnitude = 10;

		ray = rayDirection * rayMagnitude;  //ray direction and magnitude
		glm::vec3 playerPos = getUser()->getPosition(); // position of the ray user

		//the collision system is using the position of the player and that position plus the ray to make a line ( p1 = ray+playerPos, p2 = playerPos)
		GameObject* obj = collisionSys->rayCollisionCheck(ray, playerPos);

		//if a collision was found and its not the players cube
		if (obj != nullptr)
			if (obj != getUser())
			cout << "ray collision	-	" << obj->getName() << endl;

			
	}

	

private:
	InputSystem *input;
	CollisionSystem* collisionSys;

	glm::vec3 rayDirection;
	float rayMagnitude;

	glm::vec3 ray;

};