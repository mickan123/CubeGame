#pragma once

#include <vector>
#include <mutex>

#include "Chunk.h"
#include "../../Camera.h"

class ChunkRenderer
{
public:
	void AddChunk(Chunk* chunk);
	void Render(Camera* camera, Shader* shader);
	std::vector<Chunk*> chunks;
private:
	std::mutex chunksMutex;
};