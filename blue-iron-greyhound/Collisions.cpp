#include "Collisions.h"

//I was hoping to draw the bounding boxes but this doesn't work
void Collisions::draw()
{

	//CODE THAT DRAWS THE BOUNDING VOLUMES

}


bool Collisions::AABBtoAABB(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2)
{
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

void Collisions::collisionSearch()
{
	
	glm::vec3 dynamicMinimum;
	glm::vec3 dynamicMaximum;
	glm::vec3 staticMinimum;
	glm::vec3 staticMaximum;

	glm::vec3 translationVector;



/*
	//attempt at rotating the bounding boxes and it doesnt work in the slightest

	//glm::mat4 identity(1);
	//glm::mat4 modelview(1);

	//float rotation = objects[0]->getCameraRotation();
	//glm::vec3 eye = objects[0]->getTranslation();
	//glm::vec3 at = glm::vec3(eye.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), eye.y, eye.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));
	//glm::vec3 up(glm::vec3(0.0f, 1.0f, 0.0f));

	//modelview = glm::lookAt(eye, at, up);
	//
	//modelview = glm::translate(modelview, objects[0]->getPosition());
*/


	float x_overlap;
	float prev_x_overlap;


	//for every dynamic object check against all static objects for intersection. If true update the dynamic object.
	for (int i = 0; i < dynamicObjects.size(); i++)
	{
		//Grab dynamic objects position (Player). We'll need to use it a few times.
		glm::vec3 currentPosition = dynamicObjects[0]->getPosition();

		//Pull out the stored min and max out for testing and apply position (dynamic objects positions change).
		dynamicMinimum = dynMins[i] + currentPosition;
		dynamicMaximum = dynMaxs[i] + currentPosition;
		float x_overlap = -1000;
		float y_overlap = -1000;
		float z_overlap = -1000;
		float prev_x_overlap = 1000;
		

		for (int j = 0; j < staticObjects.size(); j++)
		{
			//Pull out the stored min and max out for testing
			staticMinimum = staticMins[j];
			staticMaximum = staticMaxs[j];
			
			if (isStaticAlive[j])
			{		
				//Make a collision reaction if there is an intersection
				if (AABBtoAABB(dynamicMinimum, dynamicMaximum, staticMinimum, staticMaximum))
				{
					
					isStaticAlive[j] = false;

					//translationVector = (currentPosition - staticObjects[j]->getPosition());


				//uses the last frames position to hint the direction that the player is moving. 
				//Very small value because it was only last frame so we multiply it a bit. Should really use dt for this

				translationVector = (currentPosition - prevPosition) * glm::vec3(-2.5);

					translationVector = (currentPosition - prevPosition) * glm::vec3(-2.5);


					translationVector = (currentPosition - prevPosition);


					//Randy Gaul
					//x overlap
					float extent1 = (dynamicMaximum.x - dynamicMinimum.x) / 2;

					float extent2 = (staticMaximum.x - staticMinimum.x) / 2;

					 x_overlap = extent1 + extent2 - glm::abs(translationVector.x);

					//y_overlap
					 extent1 = (dynamicMaximum.y - dynamicMinimum.y) / 2;

					 extent2 = (staticMaximum.y - staticMinimum.y) / 2;



					 y_overlap = extent1 + extent2 - glm::abs(translationVector.y);

					//z overlap
					 extent1 = (dynamicMaximum.z - dynamicMinimum.z) / 2;

					 extent2 = (staticMaximum.z - staticMinimum.z) / 2;

					 z_overlap = extent1 + extent2 - glm::abs(translationVector.z);


				
					isStaticAlive[j] = false;
					


					//uses the last frames position to hint the direction that the player is moving. 
					//Very small value because it was only last frame so we multiply it a bit. Should really use dt for this
					///translationVector = (currentPosition - prevPosition) * glm::vec3(-4);

					dynamicObjects[i]->setTranslation(currentPosition + translationVector * glm::vec3(-2));
						 //if (x_overlap != 0 && y_overlap != 0 && z_overlap)
						//dynamicObjects[i]->setTranslation(currentPosition + glm::vec3(x_overlap, y_overlap, z_overlap));


						 isStaticAlive[j] = true;

					prev_x_overlap = x_overlap;
				}
			}
		}

		//Store the current position for use as the previous position in the next frame...
		prevPosition = currentPosition;
	}

	

}

void Collisions::addStaticObject(GameObject* object)
{
	staticObjects.push_back(object);

	//Store the values we need so we aren't making multiple Get calls
	staticMins.push_back((object->getMin() * object->getScaling()) + object->getPosition());
	staticMaxs.push_back((object->getMax() * object->getScaling()) + object->getPosition());

	isStaticAlive.push_back(true);
}

void Collisions::addDynamicObject(GameObject* object)
{
	dynamicObjects.push_back(object);


	//Store the unchanging values we need but position will have to be fetched since our dynamic objects are moving
	glm::vec3 scaling = object->getScaling();

	dynMins.push_back((object->getMin() * scaling));
	dynMaxs.push_back((object->getMax() *scaling));
	

}