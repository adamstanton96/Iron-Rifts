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
	std::vector<glm::vec3> positionKeysValues;

	std::vector<double> positionKeysTimes;

	int numRotationKeys;
	std::vector<glm::vec4> rotationKeysValues;

	std::vector<double> rotationKeysTimes;

	int numScalingKeys;
	std::vector<glm::vec3> scalingKeysValues;
	//std::vector<double>
private:


};