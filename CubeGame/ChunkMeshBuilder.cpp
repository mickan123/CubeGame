#include "ChunkMeshBuilder.h"
#include <iostream>

namespace
{
	const std::vector<float> frontFace
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

	const std::vector<float> backFace
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
	};

	const std::vector<float> leftFace
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,
	};

	const std::vector<float> rightFace
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
	};

	const std::vector<float> topFace
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
	};

	const std::vector<float> bottomFace
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1,
	};

	const std::vector<float> texCoords
	{
		0, 0,
		1, 1,
		1, 0,
		1, 1,
		0, 0,
		0, 1,
	};

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

float cubeVertices[] = {
	 // Pos coords        // Tex coords
	 // Back face
	 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 // Front face
	 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 // Left face
	 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	// Right face
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 // Bottom face
	 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 // Top face
	 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

void ChunkMeshBuilder::BuildChunkMesh(Mesh* _mesh)
{
	this->mesh = _mesh;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int w = 0; w < 16; w++)
			{
				AddCube({ i, j, w });
			}
		}
	}
}

void ChunkMeshBuilder::AddFace(std::vector<float> blockFace, glm::vec3 posCoords, std::vector<float> texCoords)
{
	// 6 Coordinates for 2 triangles
	for (int i = 0; i < 6; i++)
	{
		// Add vertex positions to mesh
		mesh->vertexPositions.push_back(blockFace[i * 3 + 0] + posCoords.x);
		mesh->vertexPositions.push_back(blockFace[i * 3 + 1] + posCoords.y);
		mesh->vertexPositions.push_back(blockFace[i * 3 + 2] + posCoords.z);

		// Add texture coords to mesh
		mesh->textureCoords.push_back(texCoords[i * 2 + 0]);
		mesh->textureCoords.push_back(texCoords[i * 2 + 1]);
	}
}

void ChunkMeshBuilder::AddCube(glm::vec3 posCoords)
{
	// 6 Faces per cube
	for (int i = 0; i < 6; i++)
	{
		// 6 Vertices per face
		for (int j = 0; j < 6; j++)
		{
			int arrayOffset = i * 30 + j * 5; // 6 vertices per face * (3 vertexCoords + 2 texCoords)
			float newX = cubeVertices[arrayOffset + 0] + posCoords.x;
			float newY = cubeVertices[arrayOffset + 1] + posCoords.y;
			float newZ = cubeVertices[arrayOffset + 2] + posCoords.z;
			glm::vec3 newPos = { newX, newY, newZ };
			if (NoAdjacentFace(static_cast<Face>(i), newPos))
			{
				// Add vertex positions to mesh
				mesh->vertexPositions.push_back(newX);
				mesh->vertexPositions.push_back(newY);
				mesh->vertexPositions.push_back(newZ);

				// Add texture coords to mesh
				mesh->textureCoords.push_back(cubeVertices[arrayOffset + 3]);
				mesh->textureCoords.push_back(cubeVertices[arrayOffset + 4]);
			}
		}
	}
}

// Returns true if no adjacent face at position
bool ChunkMeshBuilder::NoAdjacentFace(Face face, glm::vec3 posCoords)
{
	glm::vec3 adjacentPos = posCoords + dirOffset[face];
	return !BlockSolid(adjacentPos) || BlockOutOfBounds(adjacentPos);
}

// Returns true if the block as given position is solid
bool ChunkMeshBuilder::BlockSolid(glm::vec3 posCoords)
{
	return true;
}

// Returns true if position is out of bounds of chunks
bool ChunkMeshBuilder::BlockOutOfBounds(glm::vec3 posCoords)
{
	return (posCoords.x < 0 || posCoords.x > 16
		 || posCoords.y < 0 || posCoords.y > 16
		 || posCoords.z < 0 || posCoords.z > 16);
}