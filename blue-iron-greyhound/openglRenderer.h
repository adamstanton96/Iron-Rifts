#ifndef openglRenderer_H
#define openglRenderer_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "RenderingSystem.h"
#include "MeshComponent.h"
class AnimatedMeshComponent;
#include "CameraComponent.h"


#include "AssimpLoader.h"
#include "OpenglUtils.h"
#include "SDLGLTextureLoader.h"

#define DEG_TO_RADIAN 0.017453293


class openglRenderer : public RenderingSystem
{
public:
	openglRenderer();
	~openglRenderer();

	void init();
	void update();
	void draw(MeshComponent* mesh);
	void loadTexture(MeshComponent* mesh, char * filename);

	void createWindow();
	void setupRenderContext();

	void destroyWindow();
	void swapBuffers();
	void clearScreen();

	void setSceneLights();

	//for testing
	void lightControl();

private:
	SDL_Window* window;												//Window Handle
	SDL_GLContext glContext;										//Context Handle

	GLuint shaderProgram;
	GLuint shaderProgramAnimated;

	// Camera/View data
	GLfloat r;
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::mat4 projection;
	stack<glm::mat4> mvStack;

};
#endif