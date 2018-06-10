#include "PlayerHUD.h"
#include "CameraComponent.h"

void PlayerHUD::init()
{
	renderer->init();
}

void PlayerHUD::setRenderer(OrthoRenderer* r)
{
	renderer = r;
}



void PlayerHUD::update(double dt)
{
	//Update huditems
	for (int i = 0; i < HudElements.size(); i++)
		HudElements[i]->update(dt);


	//Then render all hud items
	for(int i = 0; i < HudElements.size(); i++)
	renderer->render(HudElements[i]);
}

void PlayerHUD::addHudComponent(HUDitem* item)
{
	HudElements.push_back(item);

}

