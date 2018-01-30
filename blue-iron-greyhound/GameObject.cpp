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
	minimum = glm::vec3(0, 0, 0);
	maximum = glm::vec3(0, 0, 0);
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


glm::vec3 moveForward(glm::vec3 pos, float angle, float d) {
	float angles = angle;
	return glm::vec3(pos.x + d*std::sin(angle*DEG_TO_RADIAN), pos.y, pos.z - d*std::cos(angle*DEG_TO_RADIAN));
}

glm::vec3 moveRight(glm::vec3 pos, float angle, float d) {
	return glm::vec3(pos.x + d*std::cos(angle*DEG_TO_RADIAN), pos.y, pos.z + d*std::sin(angle*DEG_TO_RADIAN));
}


//TEMPORARY INPUT
void GameObject::input(double dt) 
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) position = moveForward(position, cameraRotate, 30*dt);
	if (keys[SDL_SCANCODE_S]) position = moveForward(position, cameraRotate, -30 *dt);
	if (keys[SDL_SCANCODE_A]) position = moveRight(position, cameraRotate, -30 *dt);
	if (keys[SDL_SCANCODE_D]) position = moveRight(position, cameraRotate, 30 *dt);
	if (keys[SDL_SCANCODE_R]) position.y += 30 *dt;
	if (keys[SDL_SCANCODE_F]) position.y -= 30 *dt;
	if (keys[SDL_SCANCODE_COMMA]) cameraRotate -= 50 *dt;
	if (keys[SDL_SCANCODE_PERIOD]) cameraRotate += 50 *dt;


	if (keys[SDL_SCANCODE_L]) meshRotateDeg += 2;


	if (keys[SDL_SCANCODE_1]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}

	if (keys[SDL_SCANCODE_2]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}
	
}
//////////

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

