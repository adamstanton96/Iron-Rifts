#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "GameObject.h"
#include "System.h"
#include "AABB.h"

//We need both the include and forward declaration. That's probably bad.
#include "RigidBodyComponent.h"
class RigidBodyComponent;

class CollisionSystem : public System
{
public:
	void init();
	
	void collisionCheck(RigidBodyComponent* rigidbody);

	void addStaticBody(RigidBodyComponent* rigidbody);
	void addDynamicBody(RigidBodyComponent* rigidbody);

	bool AABBtoAABB(AABB*, AABB*);

	void collisionReaction(RigidBodyComponent* rigidbody);

private:
	std::vector<RigidBodyComponent*> staticBodies;

	std::vector<RigidBodyComponent*> dynamicBodies;
	
};