#pragma once
#include "HudLogic.h"
#include <vector>
#include "PlayerMechanicsComponent.h"

class HUD_Health  : public HudLogic
{
public:
	 HUD_Health();

	 void init(GameObject* _user);
	
	 GLuint textureUpdate();
	 glm::vec3 positionUpdate();
	 glm::vec3 scaleUpdate();



private:
	std::vector<GLuint>textures;

	GLuint activeTexture;

	GameObject* user;
	PlayerMechanicsComponent* playerMech;

	

};