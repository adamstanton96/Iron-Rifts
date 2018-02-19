#include "GameObject.h"

//temp input
#include "SDL.h"

#define DEG_TO_RADIAN 0.017453293
//

//std::vector<GameObject*> GameObject::gameObjects;

GameObject::GameObject(std::string name)
{
	Object::name = name;
	//GameObject::gameObjects.push_back(this);
}


GameObject::~GameObject()
{
}


void GameObject::init()
{
	for (unsigned int i = 0; i < componentList.size(); i++) {
		componentList[i]->init();
	}
}

void GameObject::update()
{

	for (unsigned int i = 0; i < componentList.size(); i++) {
		componentList[i]->update();
	}

}

void GameObject::addComponent(Component * component)
{
	component->setUser(this);
	GameObject::componentList.push_back(component);
}

void GameObject::destroy()
{
	/*
	//Search and Remove from list
	bool found = false;
	int i = 0;
	int index = -1;
	while (!found) {
		//Checks if we have found Component
		if (GameObject::gameObjects[i]->name == GameObject::name) {
			found = true;
			index = i;
		}
		i++;
		//Reached the end
		if (i == GameObject::gameObjects.size())
			found = true;
	}
	//Remove from the gameObject list
	if (index != -1 && index < GameObject::gameObjects.size()) {
		GameObject::gameObjects[index] = GameObject::gameObjects.back();
		GameObject::gameObjects.pop_back();
	}
	*/
	//Clear Components
	for (unsigned int i = 0; i < componentList.size(); i++) {

		if (componentList[i] != nullptr) {
			componentList[i]->destroy();
			componentList[i] = nullptr;
		}
	}
}

void GameObject::destroyObj(Object *object)
{
	object->destroy();
}


void GameObject::setPosition(glm::vec3 iposition)
{
	this->position = iposition;
}

void GameObject::setRotation(float irotation)
{
	//this->rotation = irotation;
}

