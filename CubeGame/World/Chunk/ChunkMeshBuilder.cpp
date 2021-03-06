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


Mesh* ChunkMeshBuilder::BuildChunkMesh(int chunkBlocks[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE])
{
	Mesh* mesh = new Mesh();
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int w = 0; w < CHUNK_SIZE; w++)
			{
				int blockType = chunkBlocks[i*CHUNK_SIZE*CHUNK_SIZE + j*CHUNK_SIZE + w];
				if (blockType != AIR_BLOCK)
				{
					glm::vec3 cubePos = { i, j, w };
					std::vector<int> adjacentBlocktypes = GetAdjacentBlockTypes(cubePos, chunkBlocks);

					// Don't both adding cube if surrounded by solid blocks
					bool blockSurrounded = true;
					for (int i = 0; i < 6; i++)
					{
						blockSurrounded = blockSurrounded && adjacentBlocktypes[i] != AIR_BLOCK;
					}
					if (!blockSurrounded)
					{
						AddCube(mesh, cubePos, blockType, adjacentBlocktypes);
					}
				}
			}
		}
	}
	return mesh;
}


std::vector<int> ChunkMeshBuilder::GetAdjacentBlockTypes(glm::vec3 pos, int chunkBlocks[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE])
{
	std::vector<int> adjacentBlockTypes;
	for (glm::vec3 offset : dirOffset)
	{
		glm::vec3 adjacentBlockPos = pos + offset;
		if (BlockOutOfBounds(adjacentBlockPos.x, adjacentBlockPos.y, adjacentBlockPos.z))
		{
			adjacentBlockTypes.push_back(0);
		}
		else
		{
			int index = (int)adjacentBlockPos.x*CHUNK_SIZE*CHUNK_SIZE + (int)adjacentBlockPos.y*CHUNK_SIZE + (int)adjacentBlockPos.z;
			int adjacentBlockType = chunkBlocks[index];
			adjacentBlockTypes.push_back(adjacentBlockType);
		}
	}
	return adjacentBlockTypes;
}

void const ChunkMeshBuilder::AddCube(Mesh* mesh, glm::vec3 pos, int blockType, std::vector<int> adjacentBlockTypes)
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

