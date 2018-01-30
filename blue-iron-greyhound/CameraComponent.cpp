#include "CameraComponent.h"
#include "GameObject.h"

#define DEG_TO_RADIAN 0.017453293

Camera::Camera(glm::vec3 eye, glm::vec3 at, glm::vec3 up, float r)
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	this->rotation = r;
}


void Camera::init()
{
	///offset = glm::vec3(0.0, 30.0, 10.0);				//top down offset
	offset = glm::vec3(0.0, 5.0, 20.0);					//first person offset
}


void Camera::update()
{
	glm::vec3 playerPos = getUser()->getTranslation();
	this->eye = playerPos;
	this->eye += offset;

	this->rotation = getUser()->getCameraRotation();


	//Nice top down perspective
	///this->at = glm::vec3(playerPos.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), playerPos.y, playerPos.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));

	//First person perspective
	this->at = glm::vec3(eye.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), eye.y, eye.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));
	

}



glm::vec3 Camera::getEye()
{
	return eye;
}

glm::vec3 Camera::getAt()
{
	return at;
}
glm::vec3 Camera::getUp()
{
	return up;
}
float Camera::getRotation()
{
	return rotation;
}