#pragma once

#include <vector>

#include "Mesh.h"

class Model
{
public:
	Model() = default;
	Model(Mesh& mesh);
	~Model();
	void addData(Mesh& mesh);
	void bindVAO();
	void deleteData();
	void addVBO(int dimensions, std::vector<float> data);
	unsigned int getVertexCount();

private:
	unsigned int vertexCount = 0;
	unsigned int VAO = 0;
	std::vector<unsigned int> VBOs;
};