#include "TextureAtlas.h"
#include "../ResourceManager.h"
#include "../World/Constants.h"

#include <algorithm>
#include <functional>
#include <iostream>

const std::vector<int> textureFaces = {
	0, 0, 0, 0, 0, 0, // Air block ignored
	1, 1, 1, 1, 1, 1, // Dirt block all same face
	1, 1, 1, 1, 1, 2  // Grass block has grass on top
};


TextureAtlas::TextureAtlas()
{
	// Iterate over number of textures
	for (int i = 0; i < 3; i++)
	{
		// Iterate over faces
		std::vector<float> texCoords;
		for (int j = 0; j < 6; j++)
		{
			std::vector<float> faceCoords = GetTextureFace(i, j);
			texCoords.insert(texCoords.end(), faceCoords.begin(), faceCoords.end());
		}
		this->textureCoords.push_back(texCoords);
	}
}

std::vector<float> TextureAtlas::GetTextureFace(uint8_t blockType, int face)
{
	float texWidth = 1 / AtlasWidth;
	float texHeight = 1 / AtlasHeight;
	int textureType = textureFaces[6 * blockType + face];
	float xmin = textureOffsets[textureType * 2 + 0];
	float ymin = textureOffsets[textureType * 2 + 1];
	float ymax = ymin + texHeight;
	float xmax = xmin + texWidth;

	std::vector<float> texCoords = {
		xmin, ymax,
		xmax, ymin,
		xmax, ymax,
		xmax, ymin,
		xmin, ymax,
		xmin, ymin
	};

	return texCoords;
}

std::vector<float> TextureAtlas::GetTexture(uint8_t blockType)
{
	return textureCoords[blockType];
}