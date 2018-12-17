#pragma once
#include <map>

#include "Texture/Texture.h"
#include "Shader.h"


class ResourceManager
{
public:
	// Resource stores
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;

	// Load resource functions
	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	static Texture LoadTexture(const GLchar *file, GLboolean alpha, std::string name);

	// Get resource functions
	static Shader GetShader(std::string name);
	static Texture GetTexture(std::string name);

	static void Clear();
private:
	ResourceManager() {} // Prive constructor so it never gets called

	static Shader LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Texture LoadTextureFromFile(const GLchar *file, GLboolean alpha);
};