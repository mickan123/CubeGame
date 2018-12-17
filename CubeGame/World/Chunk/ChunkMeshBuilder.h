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
	Mesh* BuildChunkMesh(int chunkBlocks[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE]);
private:
	void const AddCube(Mesh* mesh, glm::vec3 pos, int blockType, std::vector<int> adjacentBlockTypes);
	std::vector<int> GetAdjacentBlockTypes(glm::vec3 pos, int chunkBlocks[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE]);
	TextureAtlas texAtlas;
};