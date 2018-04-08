#pragma once
#include "Component.h"

#define DEG_TO_RADIAN 0.017453293

class MechanicsComponent : public Component
{
public:
	MechanicsComponent() {};
	MechanicsComponent(std::string name) {};
	~MechanicsComponent() {};

	virtual void init() = 0;
	virtual void update(double dt) = 0;

	void setHealth(int health) { this->health = health; }
	void setDamage(int damage) { this->damage = damage; }
	void setWeaponRange(int weaponRange) { this->weaponRange = weaponRange; }
	void setRateOfFire(int rateOfFire) { this->rateOfFire = rateOfFire; }

	int getHealth() { return this->health; }
	int getDamage() { return this->damage; }
	int getWeaponRange() { return this->weaponRange; }
	int getRateOfFire() { return this->rateOfFire; }

protected:
	int health, damage, weaponRange, rateOfFire;
};
