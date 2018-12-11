#pragma once

#include <vector>

#include "Chunk.h"
#include "Camera.h"

class ChunkRenderer
{
public:
	void AddChunk(Chunk* chunk);
	void Render(Camera& camera, Shader& shader);

private:
	std::vector<Chunk*> chunks;
};