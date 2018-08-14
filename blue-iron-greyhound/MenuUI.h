#pragma once
#include <glm/glm.hpp>
#include<vector>
#include "UIRenderer.h"
#include "Component.h"

#include "RenderableUI.h"
#include "SDLGLTextureLoader.h"

//This class represents a menu. Consists of a background image, + sub menuUI's

class MenuUI : public RenderableUI, public Component
{
public:
	MenuUI(glm::vec3 pos, glm::vec3 scale, char *fileName);
	~MenuUI() {};

	void init();
	void update(double dt);
	
	void render();

	int getTexture();
	glm::vec3  getPosition();
	glm::vec3  getScale();


	UIRenderer* renderer;
private:
	std::vector<MenuUI> subMenus;


	GLuint texture;
	glm::vec3 position;
	glm::vec3 scale;

};