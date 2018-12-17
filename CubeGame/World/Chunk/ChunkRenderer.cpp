#include "ChunkRenderer.h"
#include "../Constants.h"
#include "../../Util/GLUtil.h"
#include <iostream>

void ChunkRenderer::AddChunk(Chunk* chunk)
{
	chunksMutex.lock();
	chunks.emplace_back(chunk);
	chunksMutex.unlock();
}


void ChunkRenderer::Render(Camera* camera, Shader* shader)
{
	shader->Use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800.0 / (float)600.0, 0.1f, 500.0f);
	glm::mat4 view = camera->GetViewMatrix();
	shader->SetMatrix4("projection", projection);
	shader->SetMatrix4("view", view);

	Texture& texture = ResourceManager::GetTexture("TextureAtlas");
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	
	chunksMutex.lock();
	for (auto& chunk : chunks)
	{
		chunk->BindChunkData();
		glm::mat4 model;
		model = glm::translate(model, chunk->chunkPos * float(CHUNK_SIZE));
		shader->SetMatrix4("model", model);
		chunk->DrawChunk();
	}
	chunksMutex.unlock();
	
}