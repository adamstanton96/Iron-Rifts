#pragma once
#include "Component.h"
#include "glm\glm.hpp"
#include "boundingVolume.h"
#include "AABB.h"
#include "Sphere.h"
#include "CollisionSystem.h"
class CollisionSystem;


class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent(string name);
	~RigidBodyComponent();

	void createAABB(glm::vec3 min, glm::vec3 max);
	void createSphere(glm::vec3 center, float radius);

	void setboundingVolume(glm::vec3 p1, glm::vec3 p2);
	

	string getBodyType();
	string getBoundingType();
	boundingVolume* getBoundingVolume();  
	void setBodyType(string bodytype);
	bool isInit();

	void init();
	void update();

	void setCollisionSystem(CollisionSystem* collisionSys);

	glm::vec3 prevPosition;
private:
	bool isInitialised;
	bool isAsleep;

	CollisionSystem* collisionSystem;

	string bodyType;    //dynamic or static
	string boundingType;

	boundingVolume* boundingVolume;
	
};
