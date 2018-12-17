#include "Model.h"
#include <iostream>
#include <glad/glad.h>

Model::Model()
{

}

Model::~Model()
{
	deleteData();
}


void Model::bindData(Mesh& mesh)
{
	if (this->VAO == 0) 
	{
		this->vertexCount = mesh.vertexPositions.size() / 3;

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
		addVBO(3, mesh.vertexPositions);
		addVBO(2, mesh.textureCoords);
	}
}


void Model::addVBO(int dimensions, std::vector<float> data)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(VBOs.size(), dimensions, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(VBOs.size());

	VBOs.push_back(VBO);
}

void Model::bindVAO()
{
	glBindVertexArray(this->VAO);
}

void Model::deleteData()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(VBOs.size(), VBOs.data());
	VBOs.clear();
	VAO = 0;
}


unsigned int Model::getVertexCount()
{
	return this->vertexCount;
}