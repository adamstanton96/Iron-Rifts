#include "openglRenderer.h"



OpenglUtils::lightStruct globalLight =
{
	{ 1.0f, 1.0f, 1.0f, 1.0f },		// ambient
	{ 0.5f, 0.5f, 0.5f, 0.5f },		// diffuse
	{ 0.0f, 0.0f, 0.0f, 0.04f },	// specular
	{ 5.0f, 5.0f, 60.0f, 0.0f }		// position
};

OpenglUtils::materialStruct material1 = {
	{ 0.4f, 0.4f, 0.4f, 1.0f },		// ambient
	{ 0.8f, 0.8f, 0.8f, 1.0f },		// diffuse
	{ 0.04, 0.04, 0.04, 0.04 },		// specular
	0.5								// shininess
};

glm::vec4 lightPos(0.0f, 5.0f, 0.0f, 0.0f);


// light attenuation
float attConstant = 1.0f;
float attLinear = 0.05f;
float attQuadratic = 0.01f;




openglRenderer::openglRenderer()
{
	createWindow();
	setupRenderContext();

	init();
}

//Initialises camera values, view values, shaders and Enables some GL features needed (like DepthTest).
void openglRenderer::init()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);

	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 1200.0f / 600.0f, 0.5f, 2000.0f);

	glm::mat4 modelview(1.0);
	mvStack.push(modelview);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	mvStack.top() = glm::lookAt(eye, at, up);

	shaderProgram = OpenglUtils::initShaders("minimal.vert", "minimal.frag");

	shaderProgramAnimated = OpenglUtils::initAnimationShaders("minimal.vert", "minimal.frag");

	lightPos = glm::vec4(0.0f, 5.0f, 0.0f, 0.0f);


}

//for testing
void openglRenderer::lightControl()
{
	//Temporary controls to help with render debugging
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_I]) lightPos.z -= 0.1;
	if (keys[SDL_SCANCODE_J])  lightPos.x -= 0.1;
	if (keys[SDL_SCANCODE_K]) lightPos.z += 0.1;
	if (keys[SDL_SCANCODE_L]) lightPos.x += 0.1;

	if (keys[SDL_SCANCODE_1]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}
	if (keys[SDL_SCANCODE_2]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	glm::vec4  tmp = mvStack.top()*lightPos;
	globalLight.position[0] = tmp.x;
	globalLight.position[1] = tmp.y;
	globalLight.position[2] = tmp.z;

	GLuint uniformIndex = glGetUniformLocation(shaderProgram, "lightPosition");
	glUniform4fv(uniformIndex, 1, globalLight.position);


}

void openglRenderer::cameraUpdate()
{
	mvStack.top()*lightPos;
	setSceneLights();

	//input light control
	lightControl();


	eye = camera->getEye();
	//r = camera->getRotation();
	at = camera->getAt();



	mvStack.top() = glm::lookAt(eye, at, up);
}





void openglRenderer::draw(MeshComponent* mesh)
{
	cameraUpdate();
	
	vector<int> meshes = mesh->getMeshes();
	vector<int> indexCounts = mesh->getIndexCounts();
	vector<int> textures = mesh->getTextures();

	int texturesize = textures.size();
	int currShader;


	for (int i = 0; i < meshes.size(); i++)
	{

		//pick a shader
		if (mesh->isAnimated)
		{			
			currShader = shaderProgramAnimated;
			glUseProgram(shaderProgramAnimated);
		}

		else
		{
			currShader = shaderProgram;
			glUseProgram(shaderProgram);
		}
		

		OpenglUtils::setUniformMatrix4fv(currShader, "projection", glm::value_ptr(projection));

		//A MeshComponent might not have the same number of meshes-textures.
		//So if we're at the end of the textures then reuse the last one used.
		if(i >= texturesize)
			glBindTexture(GL_TEXTURE_2D, textures[texturesize - 1]);
		else
			glBindTexture(GL_TEXTURE_2D, textures[i]);
	



		mvStack.push(mvStack.top());

		mvStack.top() = glm::translate(mvStack.top(), mesh->getTranslation());
		

		if (mesh->getRotate() != glm::vec3(NULL, NULL, NULL))
			mvStack.top() = glm::rotate(mvStack.top(), float(mesh->getRenderRotateDeg() * DEG_TO_RADIAN), mesh->getRotate());

		mvStack.top() = glm::scale(mvStack.top(), mesh->getScaling());

		OpenglUtils::setUniformMatrix4fv(currShader, "modelview", glm::value_ptr(mvStack.top()));
		//OpenglUtils::setMaterial(shaderProgram, mesh->getMaterial);												//Not using materials yet
		OpenglUtils::drawIndexedMesh(meshes[i], indexCounts[i], GL_TRIANGLES);
		mvStack.pop();


	}

}





//Generates a texture ID for a given filename
void openglRenderer::loadTexture(MeshComponent* mesh, char * filename)
{
	mesh->addTexture(SDLGLTextureLoader::loadBitmap(filename));
}


void openglRenderer::setSceneLights()
{
	// set light attenuation shader uniforms
	GLuint uniformIndex = glGetUniformLocation(shaderProgram, "attConst");
	glUniform1f(uniformIndex, attConstant);
	uniformIndex = glGetUniformLocation(shaderProgram, "attLinear");
	glUniform1f(uniformIndex, attLinear);
	uniformIndex = glGetUniformLocation(shaderProgram, "attQuadratic");
	glUniform1f(uniformIndex, attQuadratic);

	OpenglUtils::setLight(shaderProgram, globalLight);
	OpenglUtils::setMaterial(shaderProgram, material1);

}


//Defines the context and initialises GLEW
void openglRenderer::setupRenderContext()
{

	//Request an OpenGL 3.0 context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);										 // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);											 // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);									 // Turn on x4 multisampling anti-aliasing (MSAA)

	//Initialise glew, check init okay
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		std::cout << "GLEW not initialized correctly" << std::endl;

	cout << glGetString(GL_VERSION) << endl;											//Prints the openGL version in use

}


//initialises SDL and creates a window with openGL context
void openglRenderer::createWindow()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)														//initialise SDL
	{
		std::cout << "SDL failed" << std::endl;
	}
	else
	{

		window = SDL_CreateWindow("Iron Rifts", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	//createWindow(window title, pos on screen, pos on screan, width, height..)
			1200, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		glContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, glContext);

		if (!window)			 // Check window was created OK
			std::cout << "Window not initialized correctly" << std::endl;											//Create window (inside class window)

																	//Create openGLs rendering context
	}

}

openglRenderer::~openglRenderer()
{

}


void openglRenderer::destroyWindow()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void openglRenderer::swapBuffers()
{
	SDL_GL_SwapWindow(window);

}

void openglRenderer::clearScreen()
{

	glClearColor(0, 0, 0, 1);					//Sets glClearColour and uses GlClear to clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

