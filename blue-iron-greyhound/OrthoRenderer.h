#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<stack>
#include<vector>


#include "System.h"
#include "OpenglUtils.h"
#include "AssimpLoader.h"
#include "HUDitem.h"
//Render HUD items 

class OrthoRenderer : public System
{
public:
	OrthoRenderer(){}
	 
	~OrthoRenderer() {};

	void init();
	void render();

private:

	glm::mat4 projection;
	glm::mat4 modelveiw;

	std::stack<glm::mat4> mvStack;

	std::vector<HUDitem> hudItems;


	GLuint shaderProgram;
	GLuint meshBlock;
	int blockIndexCount;
	


	char* HUDvert
	{
		"											\n"
		"#version 330								\n"
		"											\n"
		"in vec3 in_position;						\n"
		"in vec3 in_Color;							\n"
		"out vec3 ex_Color;							\n"
		"											\n"
		"void main(void)							\n"
		"{											\n"
		"	ex_Color = in_Color;					\n"
		"	gl_Position = vec4(in_position, 1.0);	\n"
		"}                                          \n"	
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
	};

	char* HUDfrag
	{
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
		"		\n"
	};

};
