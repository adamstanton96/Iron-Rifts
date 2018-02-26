#pragma once
#include <vector>
#include <string.h>
#include <iostream>
#include <glm/glm.hpp>

class animNode
{
public:
	std::string nodeName;
	int numPositionKeys;
	std::vector<glm::vec3> positionKeys;

	int numRotationKeys;
	std::vector<glm::vec4> rotationKeys;

	int numScalingKeys;
	std::vector<glm::vec3> scalingKeys;
private:


};