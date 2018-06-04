#include "HUDitem.h"


HUDitem::HUDitem(char* textureFile, glm::vec3 pos, glm::vec3 _scale)
{
	texture = SDLGLTextureLoader::loadPNG(textureFile);
	position = pos;
	scale = _scale;
}