#include "ParticleRenderer.h"


ParticleRenderer::ParticleRenderer(Camera* camera)
{
	shaderID = OpenglUtils::initShaders(particleVert, particleFrag);
	this->camera = camera;
}



ParticleRenderer::~ParticleRenderer()
{

}

void ParticleRenderer::update()
{
	eye = camera->getEye();
	at = camera->getAt();

	mvStack.top() = glm::lookAt(eye, at, up);
}

void ParticleRenderer::init()
{
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 1200.0f / 600.0f, 0.5f, 2000.0f);

	glm::mat4 modelview(1.0);
	mvStack.push(modelview);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	mvStack.top() = glm::lookAt(eye, at, up);
}

void ParticleRenderer::draw(glm::vec3 pos)
{
	update();

	glUseProgram(shaderID);

	OpenglUtils::setUniformMatrix4fv(shaderID, "projection", glm::value_ptr(projection));

	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), pos);
	OpenglUtils::setUniformMatrix4fv(shaderID, "modelview", glm::value_ptr(mvStack.top()));
	mvStack.pop();
}