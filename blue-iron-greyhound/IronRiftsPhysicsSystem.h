#pragma once
#include "PhysicsSystem.h"

class IronRiftsPhysicsSystem : public PhysicsSystem
{
public:
	IronRiftsPhysicsSystem();
	virtual ~IronRiftsPhysicsSystem() {}

	void init();

	void addStaticBody(RigidBodyComponent* rigidbody);
	void addDynamicBody(RigidBodyComponent* rigidbody);

	//Collision Detection Using RigidBody Components...
	void collisionCheck(RigidBodyComponent* rigidbody);
	void collisionReaction(RigidBodyComponent* rigidbody);
	void displacementReaction(RigidBodyComponent* rigidbody, glm::vec3 displacementVector);

	//Raycasting...
	Ray castRay();
	std::vector<GameObject*> checkRayCollision(Ray ray);
	GameObject* checkClosest(std::vector<GameObject*>);

private:
	bool AABBtoAABB(AABB*, AABB*);
	bool OBBtoOBB(OBB* box1, OBB* box2, RigidBodyComponent* rigidbody);
	bool OBBtoAABB(OBB* box1, AABB* box2);

	std::vector<RigidBodyComponent*> staticBodies;
	std::vector<RigidBodyComponent*> dynamicBodies;

};