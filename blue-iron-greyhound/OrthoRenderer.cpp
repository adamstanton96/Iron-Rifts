#include "OrthoRenderer.h"

void OrthoRenderer::init()
{
	

	//Load shader
	shaderProgram = OpenglUtils::initShaders(HUDvert, HUDfrag);


	//Load cube mesh which will be used to display HUD textures ons
	vector<int> meshIDs;
	vector<int> indexCounts;
	vector<glm::vec3> minmax;

	AssimpLoader::loadObjectData("../../assets/cube_with_2UVs.DAE", meshIDs, indexCounts, minmax);

	meshBlock = meshIDs[0];
	blockIndexCount = indexCounts[0];

	
	//set up model view matric
	glm::mat4 modelview(1.0);
	mvStack.push(modelview);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 at = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 eye = glm::vec3(0.0f, 0.0f, 0.0f);

	mvStack.top() = glm::lookAt(eye, at, up);


	//set projection matrix
	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	HUDitem healthBar("../../assets/tex/rainTex.png", glm::vec3(0,0,0), glm::vec3(1));

	hudItems.push_back(healthBar);
	

}


void OrthoRenderer::render()
{
	glDepthMask(GL_FALSE);

	glUseProgram(shaderProgram);
	OpenglUtils::setUniformMatrix4fv(2, "projection", glm::value_ptr(projection));


	for (int i = 0; i < hudItems.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, hudItems[i].texture);

		mvStack.push(modelveiw);
		//mvStack.push(mvStack.top());

		mvStack.top() = glm::translate(mvStack.top(), hudItems[i].position);
		mvStack.top() = glm::scale(mvStack.top(), hudItems[i].scale);
		OpenglUtils::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
		OpenglUtils::drawIndexedMesh(meshBlock, blockIndexCount, GL_TRIANGLES);
		mvStack.pop();


		// remember to use at least one pop operation per push...
		mvStack.pop(); // initial matrix
	}

	
	glDepthMask(GL_TRUE);
}