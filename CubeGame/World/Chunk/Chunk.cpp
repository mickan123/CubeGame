#include "Chunk.h"
#include "../../ResourceManager.h"
#include "../../Util/GLUtil.h"

#include <iostream>

Chunk::Chunk(Mesh _mesh, glm::vec3 _chunkPos) 
	: chunkPos(_chunkPos), mesh(_mesh)
{

}

Chunk::~Chunk()
{

}

void Chunk::BindChunkData()
{
	model.bindData(mesh);
}

void Chunk::DrawChunk()
{
	model.bindVAO();
	CheckOpenGLError();
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	CheckOpenGLError();
}