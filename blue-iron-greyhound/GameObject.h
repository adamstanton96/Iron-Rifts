#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class GameObject : public Object
{
public:
	GameObject(std::string name);
	virtual ~GameObject();
	void init();
	void update();

	template<class T>
	T *getComponent();
	void addComponent(Component* component);

	void destroy();
	void destroyObj(Object *object);

	//Used to keep track of all other objects in the game...
	//static std::vector<GameObject*> gameObjects;
	//static GameObject *find(std::string name);
	//static void cleanUpObjects();


	void setPosition(glm::vec3 iposition);
	glm::vec3 getPosition() { return position; }
	float getRotation() { return rotation; }
	void setRotation(float irotation);

	/*REMOVE*/
	void setCameraRotation(float rota) { cameraRotate = rota; } //To camera (Use pointer to input system)
	float getCameraRotation() { return cameraRotate; }			//

	void setTranslation(glm::vec3 pos) { position = pos; }	// remove (use getposition)
	glm::vec3 getTranslation() { return position; }			// 



	void setRenderRotateVec(glm::vec3 rot) { meshRotate = rot; }	// remove (use rotation)
	glm::vec3 getRenderRotate() { return meshRotate; }				//
																	//
	void setRenderRotateDeg(float deg) { meshRotateDeg = deg; }		// 
	float getRenderRotateDeg() { return meshRotateDeg; }			//

//	void setCameraRotation(float rota) { cameraRotate = rota; }
	//void setTranslation(glm::vec3 pos) { position = pos; }
	void setScaling(glm::vec3 scale) { scaling = scale; }
	//void setRenderRotateVec(glm::vec3 rot) { meshRotate = rot; }
	//void setRenderRotateDeg(float deg) { meshRotateDeg = deg; }

	//glm::vec3 getTranslation() { return position; }
	//glm::vec3 getScaling() { return scaling; }
	//float getCameraRotation() { return cameraRotate; }
	//glm::vec3 getRenderRotate() { return meshRotate; }
	//float getRenderRotateDeg() { return meshRotateDeg; }



	//void setScaling(glm::vec3 scale) { scaling = scale; }	//To mesh
	glm::vec3 getScaling() { return scaling; }				//


	void setMin(glm::vec3 min) { minimum = min; }	// move somewhere elso (Add functions to return values in mesh to be used by our rigidbody)
	void setMax(glm::vec3 max) { maximum = max; }	//
	glm::vec3 getMin() { return minimum; }			//
	glm::vec3 getMax() { return maximum; }			//

	/*REMOVE end*/

	//temp input
	void input(double dt);	//remove maybe.

protected:
	std::vector<Component *> componentList;

private:
	glm::vec3 position;
	float rotation;

	/*REMOVE*/
	glm::vec3 scaling;
	glm::vec3 meshRotate;			//for the rendering
	float meshRotateDeg;
	float cameraRotate;				//for the camera

	glm::vec3 minimum;	
	glm::vec3 maximum;
	/*REMOVE end*/
};





template<class T>
T *GameObject::getComponent()
{
	bool found = false;
	T *component = nullptr;
	int i = 0;

	while (!found) {

		//Checks if we have found Component
		if (component = dynamic_cast<T*>(componentList[i]))
			found = true;

		i++;
		//Reached the end
		if (i == componentList.size())
			found = true;
	}
	return component;
}
