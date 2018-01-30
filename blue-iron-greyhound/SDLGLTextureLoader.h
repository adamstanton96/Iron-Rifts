#ifndef SDLGLTEXTURELOADER
#define SDLGLTEXTURELOADER

#include <GL/glew.h>
#include "SDL.h"
#include <iostream>


namespace SDLGLTextureLoader {

	GLuint loadBitmap(char *fname);

	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
}


#endif