#include "HUDitem.h"
#include "GameObject.h"
#include "PlayerMechanicsComponent.h"

OrthoRenderer renderer;

HUDitem::HUDitem(char* textureFile, glm::vec3 pos, glm::vec3 _scale)
{
	texture = SDLGLTextureLoader::loadPNG(textureFile);
	position = pos;
	scale = _scale;

	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUDfull.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD9.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD8.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD7.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD6.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD5.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD4.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD3.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD2.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD1.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HUD0.png"));

	renderer.init();
	
}

void HUDitem::update(double dt)
{
	//Checking player mechanics for eg Health status
	///getUser get health
	///test returned value
	///select correct texture
	PlayerMechanicsComponent* player = getUser()->getComponent<PlayerMechanicsComponent>();

	int health = player->getHealth();

	

	if (health == 100)
		texture = textures[0];
	else if(health > 90 && health < 100)
		texture = textures[1];
	else if (health > 80 && health < 90)
		texture = textures[2];
	else if (health > 70 && health < 80)
		texture = textures[3];
	else if (health > 60 && health < 70)
		texture = textures[4];
	else if (health > 50 && health < 60)
		texture = textures[5];
	else if (health > 40 && health < 50)
		texture = textures[6];
	else if (health > 30 && health < 40)
		texture = textures[7];
	else if (health > 20 && health < 30)
		texture = textures[8];
	else if (health > 10 && health < 20)
		texture = textures[9];
	else if (health < 10)
		texture = textures[10];
		

	//render itself
	renderer.render(this);
}