#pragma once

#include "../../Mesh.h"
#include "../Constants.h"
#include "../../Texture/TextureAtlas.h"

#include <glm/glm.hpp>

enum Face
{
	Back,
	Front,
	Left,
	Right,
	Bottom,
	Top,
};


class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder();
	Mesh* BuildChunkMesh(uint8_t chunkBlocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);
private:
	void const AddCube(Mesh* mesh, glm::vec3 pos, uint8_t blockType, std::vector<uint8_t> adjacentBlockTypes);
	std::vector<uint8_t> GetAdjacentBlockTypes(glm::vec3 pos, uint8_t chunkBlocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]);
	TextureAtlas texAtlas;
};