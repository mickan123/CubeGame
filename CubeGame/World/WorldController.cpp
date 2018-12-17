#include "WorldController.h"
#include "../Util/GLUtil.h"

#include <glm/gtx/transform.hpp>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

WorldController::WorldController(TerrainGenerator* _terrainGenerator, Camera* _camera, ChunkRenderer* _chunkRenderer)
{
	this->terrainGenerator = _terrainGenerator;
	this->camera = _camera;
	this->chunkRenderer = _chunkRenderer;
}

const std::vector<glm::vec2> corners =
{
	{ 1,  1},
	{ 1, -1},
	{-1, -1},
	{-1,  1}
};

const std::vector<glm::vec2> offsetDir =
{
	{ 0, -1},
	{-1,  0},
	{ 0,  1},
	{ 1,  0}
};


void WorldController::Update()
{
	int xOffset = camera->Position.x / CHUNK_SIZE;
	int zOffset = camera->Position.z / CHUNK_SIZE;
	
	// Add initial centre chunk
	AddChunk(glm::vec3(xOffset, 0, zOffset));

	// Render in a circle outwards
	for (int i = 1; i < chunkRenderDistance; i++)
	{
		for (int j=0; j<4; j++)
		{
			for (int w = 0; w < i*2; w++)
			{
				glm::vec2 relPos = corners[j] * (float)(i) + (offsetDir[j] * (float)(w));
				glm::vec3 newChunkPos = { relPos.x + xOffset, 0, relPos.y + zOffset };

				AddChunk(newChunkPos);
			}
		}
	}
}

void WorldController::AddChunk(glm::vec3 chunkPos)
{
	// Check if chunk is already being rendered
	auto& it = find_if(chunkRenderer->chunks.begin(), chunkRenderer->chunks.end(), [&chunkPos](const Chunk* obj) {return obj->chunkPos == chunkPos; });
	if (it == chunkRenderer->chunks.end())
	{
		chunkRenderer->AddChunk(GetChunk(chunkPos));
	}
}

Chunk* WorldController::GetChunk(glm::vec3 chunkPos)
{
	// Check if we have chunk cached
	auto& it = find_if(chunks.begin(), chunks.end(), [&chunkPos](const Chunk* obj) {return obj->chunkPos == chunkPos; });
	if (it == chunks.end())
	{
		clock_t start = clock();
		Chunk* newChunk = terrainGenerator->GenerateChunk(chunkPos);
		clock_t end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
		std::cout << "Time taken: " << time << std::endl;
		chunks.push_back(newChunk);
		return newChunk;
	}
	else
	{
		return *it;
	}
}