#pragma once
#include"SDL_ttf.h"
#include <GL/glew.h>
#include "Component.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "OpenglUtils.h"
#include "AssimpLoader.h"

#include "RenderingSystem.h"
//class openglRenderer;

class HUDmesh : public Component
{
public:
	HUDmesh(){}

	~HUDmesh() {}

	void init()
	{
		////Text on screen set ups
		//if (TTF_Init() == -1)
		//	std::cout << "TTF failed to initialise." << std::endl;

		//textFont = TTF_OpenFont("../../assets/MavenPro-Regular.ttf", 810);
		//if (textFont == NULL)
		//	std::cout << "Failed to open font." << std::endl;


		//textureID = 0;
		//textureID = OpenglUtils::textToTexture("Player health: ", textureID, textFont);//Actual set up of label. If dynamic, this should go in draw function

		//vector<int> meshIDs;
		//vector<int> indexCounts;
		//vector<glm::vec3> minmax;

		////Load objects into temporary containers
		//AssimpLoader::loadObjectData("../../assets/cube_with_2UVs.DAE", meshIDs, indexCounts, minmax);

		//meshIndexCount = indexCounts[0];
		//meshObject = meshIDs[0];


	}

	void update()
	{
		draw();
	}



	void draw()
	{
		render->drawBillboardedText(this);
	
	}

	RenderingSystem* render;

	GLuint textureID;
	TTF_Font * textFont;
	GLuint meshIndexCount;
	GLuint meshObject;

	glm::vec3 pos;
	glm::vec3 rot;
	

	
private:
	//openglRenderer* renderer;

	
};