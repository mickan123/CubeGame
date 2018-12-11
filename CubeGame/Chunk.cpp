#include "Chunk.h"
#include "ResourceManager.h"

#include <iostream>

Chunk::Chunk(Mesh _mesh) : model(_mesh)
{

}

Chunk::~Chunk()
{
	
}


void Chunk::DrawChunk()
{
	model.bindVAO();
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
}