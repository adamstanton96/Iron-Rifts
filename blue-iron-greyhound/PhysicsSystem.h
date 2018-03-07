#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "GameObject.h"
#include "System.h"
#include "AABB.h"
#include "OBB.h"

struct Ray { glm::vec3 startPoint, endPoint; };

class RigidBodyComponent;

class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	virtual ~PhysicsSystem() {}

	void init();

	void addStaticBody(RigidBodyComponent* rigidbody);
	void addDynamicBody(RigidBodyComponent* rigidbody);

	void collisionCheck(RigidBodyComponent* rigidbody);
	void collisionReaction(RigidBodyComponent* rigidbody);
	void displacementReaction(RigidBodyComponent* rigidbody, glm::vec3 displacementVector);
};