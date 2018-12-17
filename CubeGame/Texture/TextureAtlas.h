#pragma once

#include <string>
#include <vector>



class TextureAtlas
{
public:
	TextureAtlas();
	std::vector<float> GetTextureFace(uint8_t blockType, int face);
	std::vector<float> GetTexture(uint8_t blockType);

private:

	const float AtlasWidth = 4;
	const float AtlasHeight = 4;

	std::vector<std::vector<float>> textureCoords;

	const std::vector<float> textureVertices = {
		// Back face
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		// Front face
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		// Left face
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		// Right face
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		// Bottom face
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		// Top face
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	const std::vector<float> textureOffsets = {
		0.0f, 0.0f, // Airblock ignored
		0.0f, 0.0f, // Dirt block
		0.25f, 0.0f // Grass block
	};
};