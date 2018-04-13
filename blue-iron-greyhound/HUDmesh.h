#pragma once
#include"SDL_ttf.h"
#include <GL/glew.h>
#include "Component.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "SDLGLTextureLoader.h"
#include "AssimpLoader.h"
#include "GameObject.h"
#include "OpenglUtils.h"
#include "RenderingSystem.h"


class HUDmesh : public Component
{
public:
	HUDmesh()
	{
	
	}

	~HUDmesh() {}

	void init()
	{
		shaderID = OpenglUtils::initHUDShaders();
		//Text on screen set ups
		if (TTF_Init() == -1)
			std::cout << "TTF failed to initialise." << std::endl;

		textFont = TTF_OpenFont("../../assets/MavenPro-Regular.ttf", 810);
		if (textFont == NULL)
			std::cout << "Failed to open font." << std::endl;


		textureID = 0;
		textureID = SDLGLTextureLoader::textToTexture(this->text, textureID, textFont);//Actual set up of label. If dynamic, this should go in draw function

		vector<int> meshIDs;
		vector<int> indexCounts;
		vector<glm::vec3> minmax;

		//Load objects into temporary containers
		AssimpLoader::loadObjectData("../../assets/cube_with_2UVs.DAE", meshIDs, indexCounts, minmax);

		meshIndexCount = indexCounts[0];
		meshObject = meshIDs[0];


	}

	void update(double dt)
	{
		this->pos = this->getUser()->getPosition();
		this->scale = this->getUser()->getScaling();
		
		draw();
	}



	void draw()
	{
		render->drawBillboardedText(this);
	
	}

	void setText(const char* text)
	{
		this->text = text;
	}

	RenderingSystem* render;

	GLuint shaderID;

	GLuint textureID;
	TTF_Font * textFont;
	GLuint meshIndexCount;
	GLuint meshObject;

	const char* text;

	glm::vec3 pos;
	glm::vec3 scale;
	

	
private:
	//openglRenderer* renderer;

	
};