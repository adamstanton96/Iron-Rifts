#include "MenuUI.h"

MenuUI::MenuUI(glm::vec3 pos, glm::vec3 scale, char *fileName)
{
	texture = SDLGLTextureLoader::loadPNG(fileName);

	this->position = pos;
	this->scale = scale;
	renderer = new UIRenderer();

	init();
}

void MenuUI::init()
{
	///renderer->init();
}

void MenuUI::update(double dt)
{
	render();
}

void MenuUI::render()
{
	renderer->render(this);
}



int MenuUI::getTexture()
{
	return texture;
}


glm::vec3  MenuUI::getPosition()
{
	return position;
}


glm::vec3  MenuUI::getScale()
{
	return scale;
}
