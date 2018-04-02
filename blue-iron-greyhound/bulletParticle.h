#pragma once
#include "Component.h"
#include "glm\common.hpp"
#include <GL/glew.h>
#include "ParticleRenderer.h"

class bulletParticles : public Component
{
public:
	bulletParticles(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel, glm::vec4 col, char* tex, ParticleRenderer* renderer);
	~bulletParticles();

	void init();
	void update();
	void draw();

	void emit(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel);


private:
	//VAO & VBO's
	GLuint vao[1];
	GLuint vbo[2];

	char* texture;

	glm::vec4 colour;
	glm::vec3 position;
	glm::vec3 ray;
	glm::vec3 velocity;

	ParticleRenderer* render;
};
