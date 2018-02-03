#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "boundingVolume.h"
#include <iostream>
#include "OpenglUtils.h"
#include <vector>
#define DEG_TO_RADIAN 0.017453293
class OBB 
{
public:
	OBB(glm::vec3 min, glm::vec3 max);

	void update(glm::vec3 worldPos);
	void calculateSurfaceNormals();

	void updateVertices();
	void calculateVertices();
	
	void setminmax(glm::vec3 min, glm::vec3 max);
	void setGlobalPosition(glm::vec3 pos);
	void setRotation(float degrees, glm::vec3 roatationAxis);
	
	void printDetails();
	void draw();
	
	glm::vec3 objectSpaceMin;
	glm::vec3 objectSpaceMax;

	glm::vec4 rotatedMin;
	glm::vec4 rotatedMax;

	glm::vec3 worldSpaceMin;
	glm::vec3 worldSpaceMax;

	glm::mat4 rotation;

	glm::vec3 position;

	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> vertices;
private:


};
