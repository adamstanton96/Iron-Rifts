#pragma once
#include "Component.h"
#include "OrthoRenderer.h"
#include "HUDitem.h"
#include <vector>
//This class will hold and render all the HUD items

class PlayerHUD : public Component
{
public:
	PlayerHUD(){}

	~PlayerHUD(){};

	void init();

	void update(double dt);

	void addHudComponent(HUDitem* item); 

	void setRenderer(OrthoRenderer* renderer);

private:
	OrthoRenderer* renderer;

	std::vector<HUDitem*> HudElements;

};
