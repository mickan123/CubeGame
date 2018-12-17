#pragma once

#include "Terrain/TerrainGenerator.h"
#include "Chunk/ChunkRenderer.h"

class WorldController
{
public:
	WorldController(TerrainGenerator* _terrainGenerator, Camera* _camera, ChunkRenderer* _chunkRenderer);
	void Update();
private:
	Chunk* GetChunk(glm::vec3 relPos);
	void AddChunk(glm::vec3 chunkPos);

	ChunkRenderer* chunkRenderer;
	TerrainGenerator* terrainGenerator;
	Camera* camera;

	std::vector<Chunk*> chunks;

	int chunkRenderDistance = 8;
};