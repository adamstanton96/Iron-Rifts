#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenglUtils.h"
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#define DEG_TO_RADIAN 0.017453293

class Collisions
{
public:
	void init() { prevPosition = glm::vec3(0, 0, 0); }
	//Searches and uses 'AABBtoAABB' to find for intersections for all the dynamic objects against all the static objects 
	void collisionSearch();

	// not working. This was supposed to draw bounding boxes for ease of debugging
	void draw(); 

	//Checks two AABB's fo intersection
	bool AABBtoAABB(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2);

	//Methods for adding objects 
	void addStaticObject(GameObject* object);
	void addDynamicObject(GameObject* object);
private:
	glm::vec3 prevPosition;

	std::vector<GameObject*> staticObjects;
	std::vector<GameObject*> dynamicObjects;

	std::vector<glm::vec3> staticMins;
	std::vector<glm::vec3> staticMaxs;

	std::vector<glm::vec3> dynMins;
	std::vector<glm::vec3> dynMaxs;

	std::vector<bool> isStaticAlive;
};