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
				if (OBBtoOBB(bound, (OBB*)staticBodies[i]->getBoundingVolume(), rigidbody))
				{
					collisionReaction(rigidbody);
				}
		}

		//test against all other dynamic bodies bodies
		for (unsigned int i = 0; i < dynamicBodies.size(); i++)
		{
			if (dynamicBodies[i] != rigidbody)
			if (dynamicBodies[i]->getBoundingType() == "AABB")
				if (OBBtoAABB(bound, (AABB*)dynamicBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}
			if (dynamicBodies[i] != rigidbody)
			if (dynamicBodies[i]->getBoundingType() == "OBB")
				if (OBBtoOBB(bound, (OBB*)dynamicBodies[i]->getBoundingVolume(), rigidbody))
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











bool CollisionSystem::OBBtoOBB(OBB* box1, OBB* box2 , RigidBodyComponent* rigidbody)
{

	// 1) Project each vertice of each shape onto the given axis of seperation (1 of 6... or 3?)
	// 2) Take the min and max projected point of each shape       
	// 3) If any of these projected min and maxs do not overlap then exit, no intersection found
	//std::vector<float> SatTest(std::vector<glm::vec3> pointset1, std::vector<glm::vec3> pointset2, glm::vec3 axis)
	
	float minProj1;
	float maxProj1;

	float minProj2;
	float maxProj2;

		std::vector<glm::vec3> vertices1 = box1->worldVertices;
		std::vector<glm::vec3> vertices2 = box2->worldVertices;

		std::vector<glm::vec3> faces = box2->faceNormals;

		glm::vec3 axis;

		int i;
		glm::vec3 Vec;
		bool xOverlap;
		bool zOverlap;

		xOverlap = false;
		zOverlap = false;

		for (i = 3; i < 6; i++)
		{
			minProj1 = 1000;
			maxProj1 = -1000;

			minProj2 = 1000;
			maxProj2 = -1000;


			axis = faces[i];

			std::cout << "Axis: " << i << std::endl;
			std::cout << "(" << axis.x << ", " << axis.y << ", " << axis.z << ")" << std::endl;


			for (int j = 0; j < vertices1.size(); j++)
			{
				float dotproduct1 = glm::dot(vertices1[j], axis);

				if (dotproduct1 < minProj1) minProj1 = dotproduct1;
				if (dotproduct1 > maxProj1) maxProj1 = dotproduct1;

			}

			for (int j = 0; j < vertices2.size(); j++)
			{
				float dotproduct2 = glm::dot(vertices2[j], axis);

				if (dotproduct2 < minProj2) minProj2 = dotproduct2;
				if (dotproduct2 > maxProj2) maxProj2 = dotproduct2;
			}


			/*std::cout << "Projection" << " "<< i << ": " << std::endl;
			std::cout << "MinProj1: " << minProj1;
			std::cout << "		MaxProj1: " << maxProj1 << std::endl;

			std::cout << "minProj2: " << minProj2;
			std::cout << "		maxProj2: " << maxProj2 << std::endl;*/

			//::cout << "Axis Vector: ";
			//std::cout << "(" << axis.x << ", " << axis.y << ", " << axis.z << ")" << std::endl;

		
			//z axis
			if (i == 3)
			{
				std::cout << "Axis Vector: ";
				std::cout << "(" << axis.x << ", " << axis.y << ", " << axis.z << ")" << std::endl;
				if (maxProj1 > minProj2 && minProj1 < minProj2)
				{
					Vec.z = ((maxProj1 - minProj2) * -1);// *axis.z;

					//Vec = -axis * (maxProj1 - minProj2);

					zOverlap = true;
					//std::cout << "Z overlap: ";
				}

				if (minProj1 < maxProj2 && maxProj1 > maxProj2)
				{
					zOverlap = true;
					Vec.z = (maxProj2 - minProj1);// *axis.z;

					//Vec = axis * (maxProj2 - minProj1);
					//std::cout << "Z overlap: ";
				}
				if (minProj2 < minProj1 && maxProj1 < maxProj2)
				{
					zOverlap = true;
					Vec.z = (maxProj2 - minProj1);// *axis.z;
					//Vec = axis * (maxProj2 - minProj1);
					//std::cout << "Z overlap: ";
				}
			}


			//x axis
			if (i == 4)
			{
				//std::cout << "Displacement Vector: ";

				if (maxProj1 > minProj2 && minProj1 < minProj2)
				{
					xOverlap = true;
					Vec.x = ((maxProj1 - minProj2) * -1);// *axis.x;
					//Vec = -axis * (maxProj1 - minProj2);
					//std::cout << "X overlap: ";
				}

				if (minProj1 < maxProj2 && maxProj1 > maxProj2)
				{
					xOverlap = true;
					Vec.x = (maxProj2 - minProj1);// *axis.x;
					//Vec = axis * (maxProj2 - minProj1);
					//std::cout << "X overlap: ";
				}

				//encolsed completed in this plane
				if (minProj2 < minProj1 && maxProj1 < maxProj2)
				{
					xOverlap = true;
					Vec.x = (maxProj2 - minProj1);// *axis.x;
					//Vec = axis * (maxProj2 - minProj1);
					//std::cout << "Z overlap: ";
				}

			}


		}

			//y axis
			//if (i == 5)
				//Vec.y = maxProj1 - minProj2;

			//if (i == 3)
			//if (maxProj1 < minProj2 || minProj1 > maxProj2)
			//	return false;
			
	


		if ((xOverlap && zOverlap) == true)
		{
			if (Vec.x < Vec.z)
			{
				Vec.z = 0;
				Vec.y = 0;
			}
			else
			{
				Vec.x = 0;
				Vec.y = 0;
			}

			std::cout << "Displacement Vector: ";
			std::cout << "(" << Vec.x << ", " << Vec.y << ", " << Vec.z << ")" << std::endl;

			displacementReaction(rigidbody, Vec);
		}
		

	/*	std::vector<float> projectedPoints;

		projectedPoints.push_back(minProj1);
		projectedPoints.push_back(maxProj1);
		projectedPoints.push_back(minProj2);
		projectedPoints.push_back(maxProj2);*/

		
		//return projectedPoints;

	

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





