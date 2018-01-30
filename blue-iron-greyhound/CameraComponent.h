#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include "Component.h"



class Camera : public Component
{
public:
	Camera() {}
	Camera(glm::vec3 eye, glm::vec3 at, glm::vec3 up, float r);
	~Camera() {};

	void init();
	void update();

	glm::vec3 getEye();
	glm::vec3 getAt();
	glm::vec3 getUp();
	float getRotation();

private:

	glm::vec3 offset;		//affects the cameras position relevant to player object
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	float rotation;


};


#endif