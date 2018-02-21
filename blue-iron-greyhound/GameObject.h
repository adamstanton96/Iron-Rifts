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

	void setRotationAxis(glm::vec3 rot) { rotationAxis = rot; }	
	glm::vec3 getRotationAxis() { return rotationAxis; }				
															
	void setRotationDegrees(float deg) { rotationDegrees = deg; }		
	float getRotationDegrees() { return rotationDegrees; }			



	void setScaling(glm::vec3 scale) { scaling = scale; }	
	glm::vec3 getScaling() { return scaling; }				


protected:
	std::vector<Component *> componentList;

private:
	glm::vec3 position;

	glm::vec3 scaling;
	glm::vec3 rotationAxis;			
	float rotationDegrees;
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
