#include "bulletParticle.h"


bulletParticles::bulletParticles(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel, glm::vec4 col, char* tex, ParticleRenderer* renderer)
{
	position = pos;
	velocity = vel;
	colour = col; //Red bullet

	ray = trajectory;

	render = renderer;
	texture = tex;
}


bulletParticles::~bulletParticles()
{

}

void bulletParticles::init()
{
	render->initTexture(texture);

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

	velocity = trajectory * vel;
	
}

void bulletParticles::update()
{
	position += velocity;
	draw();
}


void bulletParticles::draw()
{

	render->updateShader(position);

	//Update the positions...
	glBindVertexArray(vao[0]); 
							  
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec3), &position, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     
						
	//Colour doesn't seem to be setting?
	glBindVertexArray(vao[1]); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(glm::vec4), &colour, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);    

	glPointSize(100);


	//pre draw settings
	glEnable(GL_POINT_SPRITE); //use for particles.
	glEnable(GL_PROGRAM_POINT_SIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glDepthMask(0);


	
	//Draw all of our particles...
	for (int i = 0; i < 1; i++)
	{
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glBindVertexArray(0);

	////post draw settings
	glDisable(GL_BLEND);
//	glDepthMask(1);
	glDepthMask(GL_TRUE);
}


