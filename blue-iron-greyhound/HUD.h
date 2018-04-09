#pragma once
#include "GameObject.h"
#include"SDL_ttf.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>
#include "OpenglUtils.h"

class HUD : Component
{
public:
 	void init();
	void update();
	void draw(SDL_Window * window);
	GLuint textToTexture(const char * str, GLuint textID);
protected:
	GLuint labels[5];
	TTF_Font * textFont;
	glm::vec3 position;
	glm::vec3 scaling;
	glm::vec3 rotationAxis;
	GLuint shaderProgram;
	SDL_Window * window;
	GLuint meshIndexCount = 0;
	GLuint meshObjects[1];
};