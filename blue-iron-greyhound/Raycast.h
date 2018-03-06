#pragma once
#include "Component.h"
#include "InputSystem.h"
#include <iostream>


class Raycast : public Component
{
public:
	Raycast(InputSystem *input)
	{
		this->input = input;
	}

	~Raycast(){}


	void update() 
	{
		//glm::vec2 mousePos = input->getMousePosition();

		//glm::vec2 playerForwrd(0, -1);  //x,z
		//float playerRotation = getUser()->getRotationDegrees();

		//ray.x = glm::cos(playerRotation * 0) - glm::sin(playerRotation*-1);
		//ray.y = glm::sin(playerRotation * 0) - glm::cos(playerRotation*-1);
	
		//std::cout << glm::normalize(ray.x) << ", " << glm::normalize(ray.y) << std::endl;



			
	}

	void init()
	{

	}

private:
	InputSystem *input;

	glm::vec2 ray;
};