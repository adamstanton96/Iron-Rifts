#pragma once
class OrthoRenderer;
#include "SDLGLTextureLoader.h"
#include <glm/glm.hpp>
#include<vector>
#include "OrthoRenderer.h"
#include "Component.h"



class HUDitem : public Component
{
public:
	HUDitem(char* textureFile, glm::vec3 pos, glm::vec3 scale);
	~HUDitem(){}

	void update(double dt);

	void init(){}

	GLuint texture;
	glm::vec3 position;
	glm::vec3 scale;

	////////
	std::vector<GLuint>textures;

	////////

	
private:
	
	
};
