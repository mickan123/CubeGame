#include "ChunkMeshBuilder.h"
#include <iostream>

ChunkMeshBuilder::ChunkMeshBuilder()
{

}

// Returns true if position is out of bounds of chunks
constexpr bool BlockOutOfBounds(int x, int y, int z)
{
	return (x < 0 || x > CHUNK_SIZE - 1
		 || y < 0 || y > CHUNK_SIZE - 1
		 || z < 0 || z > CHUNK_SIZE - 1);
}

const std::vector<glm::vec3> dirOffset
{
	{  0,  0, -1 }, // Back
	{  0,  0,  1 }, // Front
	{ -1,  0,  0 }, // Left
	{  1,  0,  0 }, // Right
	{  0, -1,  0 }, // Bottom 
	{  0,  1,  0 }, // Top
};

const float cubeVertices[] = {
	 // Back face
	 0.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,
	 // Front face
	 0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 1.0f,
	 // Left face
	 0.0f, 1.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 
	 0.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 1.0f,
	// Right face
	 1.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 0.0f, 
	 1.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,
	 // Bottom face
	 0.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 0.0f,
	 // Top face
	 0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,
	 0.0f, 1.0f, 0.0f,
	 0.0f, 1.0f, 1.0f,
};

Mesh* ChunkMeshBuilder::BuildChunkMesh(uint8_t chunkBlocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE])
{
	Mesh* mesh = new Mesh();
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int w = 0; w < CHUNK_SIZE; w++)
			{
				if (chunkBlocks[i][j][w] != AIR_BLOCK)
				{
					glm::vec3 cubePos = { i, j, w };
					std::vector<uint8_t> adjacentBlocktypes = GetAdjacentBlockTypes(cubePos, chunkBlocks);
					AddCube(mesh, cubePos, chunkBlocks[i][j][w], adjacentBlocktypes);
				}
			}
		}
	}
	return mesh;
}


std::vector<uint8_t> ChunkMeshBuilder::GetAdjacentBlockTypes(glm::vec3 pos, uint8_t chunkBlocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE])
{
	std::vector<uint8_t> adjacentBlockTypes;
	for (glm::vec3 offset : dirOffset)
	{
		glm::vec3 adjacentBlockPos = pos + offset;
		if (BlockOutOfBounds(adjacentBlockPos.x, adjacentBlockPos.y, adjacentBlockPos.z))
		{
			adjacentBlockTypes.push_back((uint8_t)0);
		}
		else
		{
			uint8_t adjacentBlockType = chunkBlocks[(int)adjacentBlockPos.x][(int)adjacentBlockPos.y][(int)adjacentBlockPos.z];
			adjacentBlockTypes.push_back(adjacentBlockType);
		}
	}
	return adjacentBlockTypes;
}

void const ChunkMeshBuilder::AddCube(Mesh* mesh, glm::vec3 pos, uint8_t blockType, std::vector<uint8_t> adjacentBlockTypes)
{
	// 6 Faces per cube
	for (int i = 0; i < 6; i++)
	{
		if (!adjacentBlockTypes[i])
		{
			// 6 Vertices per face
			for (int j = 0; j < 6; j++)
			{
				int arrayOffset = i * 18 + j * 3;
				float newX = cubeVertices[arrayOffset + 0] + pos.x;
				float newY = cubeVertices[arrayOffset + 1] + pos.y;
				float newZ = cubeVertices[arrayOffset + 2] + pos.z;

				// Add vertex positions to mesh
				mesh->vertexPositions.push_back(newX);
				mesh->vertexPositions.push_back(newY);
				mesh->vertexPositions.push_back(newZ);

			}
			// Get texture coords
			std::vector<float> texCoords = texAtlas.GetTextureFace(blockType, i);
			mesh->textureCoords.insert(mesh->textureCoords.end(), texCoords.begin(), texCoords.end());
		}
	}
}

