#include "bulletParticle.h"


bulletParticles::bulletParticles(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel, ParticleRenderer* renderer)
{
	position = pos;
	velocity = vel;
	colour = glm::vec4(1); //white bullet

	ray = trajectory;

	render = renderer;
}


bulletParticles::~bulletParticles()
{

}

void bulletParticles::init()
{
	
	glGenVertexArrays(1, vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao[0]); 
						
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec3), &position, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), &colour, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void bulletParticles::emit(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel)
{
	position = pos;
	velocity = vel;
	//ray = trajectory;
	//colour = glm::vec4(1); //white bullet
}

void bulletParticles::update()
{
	position += velocity;
	draw();
}


void bulletParticles::draw()
{

	//Update the positions...
	glBindVertexArray(vao[0]); 
							  
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec3), &position, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     
							
	glBindVertexArray(vao[1]); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), &colour, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);    

	glPointSize(5);

	render->draw(position, colour);
	
	//Draw all of our particles...
	for (int i = 0; i < 2; i++)
	{
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glBindVertexArray(0);
}


