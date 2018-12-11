#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	Texture();
	void Bind() const;
	void Generate(GLuint width, GLuint height, unsigned char* data);

	unsigned int Width, Height;
	unsigned int Internal_Format;
	unsigned int Image_Format;
	unsigned int ID;
	unsigned int Wrap_S;
	unsigned int Wrap_T;
	unsigned int Filter_Min;
	unsigned int Filter_Max;

private:
	
};