#pragma once

class boundingVolume
{
public:
	boundingVolume() {};

	virtual void update(glm::vec3 worldPos) = 0;

};
