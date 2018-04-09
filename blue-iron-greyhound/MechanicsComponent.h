#pragma once
#include "Component.h"
#include "AudioSystem.h"
#include "PhysicsSystem.h"
#include "bulletParticle.h"
//timer
#include <ctime>
#include <cstdlib>
#include "time.h"

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

	void setAudio(AudioSystem *audio) { this->audio = audio; }
	void setPhysics(PhysicsSystem *physics) { this->physics = physics; }
	void setParticleRenderer(bulletParticle *particleRenderer) { this->particleRenderer = particleRenderer; }

	int getHealth() { return this->health; }
	int getDamage() { return this->damage; }
	int getWeaponRange() { return this->weaponRange; }
	int getRateOfFire() { return this->rateOfFire; }

	AudioSystem *getAudio() { return this->audio; }
	PhysicsSystem *getPhysics() { return this->physics; }
	bulletParticle *getParticleRenderer() { return this->particleRenderer; }

protected:
	int health, damage, weaponRange, rateOfFire;

	AudioSystem *audio;
	PhysicsSystem *physics;
	bulletParticle *particleRenderer;

	std::clock_t start;
};
