#pragma once
#include <glm/glm.hpp>
//Defines the information needed for rendering a 2D object.

class RenderableUI
{
public:
	virtual int getTexture() = 0;
	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 getScale() = 0;

private:
};
