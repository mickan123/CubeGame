#include "ChunkRenderer.h"
#include <iostream>

void ChunkRenderer::AddChunk(Chunk* chunk)
{
	chunks.push_back(chunk);
}


void ChunkRenderer::Render(Camera& camera, Shader& shader)
{
	shader.Use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800.0 / (float)600.0, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.SetMatrix4("projection", projection);
	shader.SetMatrix4("view", view);
	
	glm::mat4 model;
	model = glm::translate(model, { 0, 0, 0 });
	shader.SetMatrix4("model", model);

	Texture& texture = ResourceManager::GetTexture("dirt");
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	for (auto& chunk : chunks)
	{
		chunk->DrawChunk();
	}

}