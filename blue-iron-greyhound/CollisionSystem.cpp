#include "CollisionSystem.h"



void CollisionSystem::init() 
{

}



void CollisionSystem::collisionCheck(RigidBodyComponent* rigidbody)
{
	
	glm::vec3 currentPosition = rigidbody->getUser()->getTranslation();

	
	if (rigidbody->getBoundingType() == "AABB")
	{
		AABB* bound = (AABB*)rigidbody->getBoundingVolume();

		//test against all static bodies
		for (unsigned int i = 0; i < staticBodies.size(); i++)
		{
			if (staticBodies[i]->getBoundingType() == "AABB")
				if (AABBtoAABB(bound, (AABB*)staticBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}		
		}

		//test against all other dynamic bodies bodies
		for (unsigned int i = 0; i < dynamicBodies.size(); i++)
		{
			if(dynamicBodies[i] != rigidbody)							//make sure it doesn't test against itself or it will warp speed us far away...
				if (dynamicBodies[i]->getBoundingType() == "AABB")
					if (AABBtoAABB(bound, (AABB*)dynamicBodies[i]->getBoundingVolume()))
					{
						collisionReaction(rigidbody);
					}
		}
	}
	else if (rigidbody->getBoundingType() == "OBB")
	{
		OBB* bound = (OBB*)rigidbody->getBoundingVolume();

		//test against all static bodies
		for (unsigned int i = 0; i < staticBodies.size(); i++)
		{
			if (staticBodies[i]->getBoundingType() == "AABB")
				if (OBBtoAABB(bound, (AABB*)staticBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}

			if (staticBodies[i]->getBoundingType() == "OBB")
				if (OBBtoOBB(bound, (OBB*)staticBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}
		}

		//test against all other dynamic bodies bodies
		for (unsigned int i = 0; i < dynamicBodies.size(); i++)
		{
			if (dynamicBodies[i]->getBoundingType() == "AABB")
				if (OBBtoAABB(bound, (AABB*)dynamicBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}

			if (dynamicBodies[i]->getBoundingType() == "OBB")
				if (OBBtoOBB(bound, (OBB*)dynamicBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}
		}
	}
	else
	{
		std::cout << "CollisionSystem/collisionCheck: Unsupported or invalid boundingtype" << std::endl;
	}

	
	rigidbody->prevPosition = currentPosition;
		
	
}


void CollisionSystem::collisionReaction(RigidBodyComponent* rigidbody)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getTranslation();


	glm::vec3 translationVector = (currentPosition - rigidbody->prevPosition) * glm::vec3(-2.5);

	translationVector = (currentPosition - rigidbody->prevPosition);

	rigidbody->getUser()->setTranslation(currentPosition + translationVector * glm::vec3(-2));


}

void CollisionSystem::displacementReaction(RigidBodyComponent* rigidbody, glm::vec3 displacementVector)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getTranslation();

	rigidbody->getUser()->setTranslation(currentPosition + displacementVector);

}





bool CollisionSystem::OBBtoOBB(OBB* box1, OBB* box2)
{


	return false;
}


bool CollisionSystem::AABBtoAABB(AABB* box1, AABB* box2)
{
	
	glm::vec3 min1 = box1->worldSpaceMin;
	glm::vec3 max1 = box1->worldSpaceMax;

	glm::vec3 min2 = box2->worldSpaceMin;
	glm::vec3 max2 = box2->worldSpaceMax;

	// Collision tests. if any tests are false then theres no intersection.
	if (max1.x < min2.x || min1.x > max2.x)
		return false;
	if (max1.y < min2.y || min1.y > max2.y)
		return false;
	if (max1.z < min2.z || min1.z > max2.z)
		return false;
	else
		return true;

}



bool CollisionSystem::OBBtoAABB(OBB* box1, AABB* box2)
{


	return false;
}



void CollisionSystem::addStaticBody(RigidBodyComponent* rigidbody)
{
	staticBodies.push_back(rigidbody);
}

void CollisionSystem::addDynamicBody(RigidBodyComponent* rigidbody)
{
	dynamicBodies.push_back(rigidbody);
}





