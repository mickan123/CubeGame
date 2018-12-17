#include "GLUtil.h"

// Prints errors if they have occurred
void CheckOpenGLError()
{
	GLenum err;
	int errorCount = 1;
	while ((err = glGetError()) != GL_NO_ERROR) {

		std::cout << "Error num " << errorCount++ << std::endl;
		std::cout << "OpenGL error: " << err << std::endl;
	}
}