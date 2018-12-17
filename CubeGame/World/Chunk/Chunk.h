#pragma once

#include "../../ResourceManager.h"
#include "../../Camera.h"
#include "../../Mesh.h"
#include "../../Model.h"

class Chunk
{
public:
	Chunk(Mesh _mesh, glm::vec3 _chunkPos);
	~Chunk();
	void DrawChunk();
	void BindChunkData();
	const glm::vec3 chunkPos;
private:
	Model model;
	Mesh mesh;
};