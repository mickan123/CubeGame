#include "TerrainGenerator.h"

#include <cstdint>
#include <time.h>
#include <iostream>

TerrainGenerator::TerrainGenerator() : chunkMeshBuilder()
{

}

Chunk* TerrainGenerator::GenerateChunk(glm::vec3 chunkPos)
{
	uint8_t chunkBlocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			double noise = pn.noise((float)(chunkPos.x * CHUNK_SIZE + x)/50.0, (float)(chunkPos.z * CHUNK_SIZE + z)/50.0, 0);
			int height = floor(noise * (float)CHUNK_SIZE);
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				if (y == height)
				{
					chunkBlocks[x][y][z] = GRASS_BLOCK;
				}
				else
				{
					chunkBlocks[x][y][z] = (y > height) ? AIR_BLOCK : DIRT_BLOCK;
				}
			}
		}
	}

	Mesh* newMesh = chunkMeshBuilder.BuildChunkMesh(chunkBlocks);

	return new Chunk(*newMesh, chunkPos);
}

