#include "bulletParticle.h"


bulletParticles::bulletParticles(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel)
{
	position = pos;
	velocity = vel;
	colour = glm::vec4(1); //white bullet
}


bulletParticles::~bulletParticles()
{

}

void bulletParticles::init()
{
	//Initialise the VAO/VBO's...
	glGenVertexArrays(1, vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao[0]); // bind VAO 0 as current object.

							   // Position data in attribute index 0, 3 floats per vertex.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // bind VBO for positions.
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec3), &position, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     // Enable attribute index 0.

									  // Colours data in attribute 1, 3 floats per vertex.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // bind VBO for colours.
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), &colour, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);    // Enable attribute index 1.
	glBindVertexArray(0);
}

void bulletParticles::emit(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel)
{
	position = pos;
	velocity = vel;
	ray = trajectory;
	//colour = glm::vec4(1); //white bullet
}

void bulletParticles::update()
{
	position += velocity;
}


void bulletParticles::draw()
{
	//Update the positions...
	glBindVertexArray(vao[0]); // bind VAO 0 as current object.
							   // particle data may have been updated - so need to resend to GPU.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // bind VBO 0.
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec3), &position, GL_DYNAMIC_DRAW);
	// Position data in attribute index 0, 3 floats per vertex.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     // Enable attribute index.

									  //Update the colours...
	glBindVertexArray(vao[1]); // bind VAO 0 as current object.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // bind VBO 0.
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), &colour, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     // Enable attribute index.


									  //Draw all of our particles...
	for (int i = 0; i < 1; i++)
	{
		//glBindTexture(GL_TEXTURE_2D, texID[i]);
		glDrawArrays(GL_POINTS, i, 1);
	}
	glBindVertexArray(0);
}


