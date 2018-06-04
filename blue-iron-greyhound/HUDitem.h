#pragma once
#include "SDLGLTextureLoader.h"
#include <glm/glm.hpp>

class HUDitem
{
public:
	HUDitem(char* textureFile, glm::vec3 pos, glm::vec3 scale);

	GLuint texture;
	glm::vec3 position;
	glm::vec3 scale;
private:
	
};
