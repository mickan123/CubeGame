#pragma once

#include "Cube.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"

class Chunk
{
public:
	Chunk(Mesh _mesh);
	~Chunk();
	void DrawChunk();

private:
	Model model;
};