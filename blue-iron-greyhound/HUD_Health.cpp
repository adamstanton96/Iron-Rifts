#include "HUD_Health.h"

HUD_Health::HUD_Health()
{
	initialised = false;

	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUDfull.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD9.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD8.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD7.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD6.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD5.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD4.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD3.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD2.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD1.png"));
	textures.push_back(SDLGLTextureLoader::loadPNG("../../assets/tex/HealthBar/HUD0.png"));
}

void HUD_Health::init(GameObject* _user)
{
	this->user = _user;

	playerMech = user->getComponent<MechanicsComponent>();

	initialised = true;
}

GLuint HUD_Health::textureUpdate()
{
	int health = playerMech->getHealth();

	
	if (health == 100)
		activeTexture = textures[0];
	else if (health > 90 && health < 100)
		activeTexture = textures[1];
	else if (health > 80 && health < 90)
		activeTexture = textures[2];
	else if (health > 70 && health < 80)
		activeTexture = textures[3];
	else if (health > 60 && health < 70)
		activeTexture = textures[4];
	else if (health > 50 && health < 60)
		activeTexture = textures[5];
	else if (health > 40 && health < 50)
		activeTexture = textures[6];
	else if (health > 30 && health < 40)
		activeTexture = textures[7];
	else if (health > 20 && health < 30)
		activeTexture = textures[8];
	else if (health > 10 && health < 20)
		activeTexture = textures[9];
	else if (health < 10)
		activeTexture = textures[10];


	return activeTexture;
}


glm::vec3 HUD_Health::positionUpdate()
{
	return glm::vec3(0);
}


glm::vec3 HUD_Health::scaleUpdate()
{
	return glm::vec3(0);
}