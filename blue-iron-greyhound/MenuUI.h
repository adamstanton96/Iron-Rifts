#pragma once
#include <glm/glm.hpp>
#include<vector>
#include "OrthoRenderer.h"
#include "Component.h"

//This class represents a menu. Consists of a background image, + sub menuUI's

class MenuUI
{
public:
	MenuUI();

	void render();


private:
	std::vector<MenuUI> subMenus;

	OrthoRenderer renderer;

};