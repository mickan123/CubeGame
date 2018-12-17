#pragma once

#include "../Chunk/Chunk.h"
#include "../Constants.h"
#include "../Chunk/ChunkMeshBuilder.h"
#include "../../Maths/PerlinNoise.h"

class TerrainGenerator
{
public:
	TerrainGenerator();
	Chunk* GenerateChunk(glm::vec3 chunkPos);

private:
	ChunkMeshBuilder chunkMeshBuilder;
	PerlinNoise pn;
};