#include "HUD.h"


 

void HUD::init() {
	// set up TrueType / SDL_ttf taken from rt3d HUD Label Example
	if (TTF_Init() == -1)
		cout << "TTF failed to initialise." << endl;

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 48);
	if (textFont == NULL)
		cout << "Failed to open font." << endl;

	labels[0] = textToTexture(" Score: original ", 0);

	shaderProgram = OpenglUtils::initShaders("phong-tex.vert", "phong-tex.frag");

}
void HUD::update()
{
 	draw(window);
}

// textToTexture taken from rt3d HUD Label Example
GLuint HUD::textToTexture(const char * str, GLuint textID) {
	GLuint texture = textID;
	TTF_Font * font = textFont;

	SDL_Surface * stringImage = TTF_RenderText_Blended(font, str, { 255, 255, 255 });

	if (stringImage == NULL) {
		std::cout << "String surface not created." << std::endl;
	}

	if (texture == 0) {
		glGenTextures(1, &texture);
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stringImage->w, stringImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, NULL);

	SDL_FreeSurface(stringImage);
	return texture;
}

void HUD::draw(SDL_Window * window) {
	glm::mat4 modelview(1.0);

	glDepthMask(GL_TRUE);

	glActiveTexture(GL_TEXTURE0);
	labels[0] = textToTexture("Score: update", labels[0]);
	glBindTexture(GL_TEXTURE_2D, labels[0]);
	modelview = glm::translate(modelview, glm::vec3(-3.2f, 2.5f, -5.0f));
	modelview = glm::scale(modelview, glm::vec3(0.5f, 0.5f, 0.0f));
	OpenglUtils::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(modelview));
 

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	OpenglUtils::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	SDL_GL_SwapWindow(window); // swap buffers

}