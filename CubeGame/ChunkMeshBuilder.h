#pragma once

#include "Mesh.h"

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
	void BuildChunkMesh(Mesh* mesh);
private:
	void AddFace(std::vector<float> blockFace, glm::vec3 posCoords, std::vector<float> texCoords); \
	void AddCube(glm::vec3 posCoords);
	bool BlockSolid(glm::vec3 posCoords);
	bool BlockOutOfBounds(glm::vec3 posCoords);
	bool NoAdjacentFace(Face face, glm::vec3 posCoords);
	Mesh* mesh;
};