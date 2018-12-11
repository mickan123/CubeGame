#include "Game.h"
#include "ResourceManager.h"
#include "Cube.h"
#include "ChunkMeshBuilder.h"
#include "ChunkRenderer.h"
#include "Chunk.h"
#include <GLFW\glfw3.h>

ChunkRenderer *chunkRenderer;

Game::Game()
{

}

Game::~Game()
{
	delete chunkRenderer;
}

void Game::SetWindow(GLFWwindow* _window)
{
	this->window = _window;
}

void Game::SetCamera(Camera* _camera)
{
	this->camera = _camera;
}


void Game::Init()
{
	ResourceManager::LoadShader("Resources/Shaders/Cube.vs", "Resources/Shaders/Cube.fs", nullptr, "cube");
	ResourceManager::LoadTexture("Resources/Textures/container.jpg", false, "container");
	ResourceManager::LoadTexture("Resources/Textures/dice_texture.png", false, "dice");
	ResourceManager::LoadTexture("Resources/Textures/dirt.png", false, "dirt");

	Cube cube = Cube(ResourceManager::GetShader("cube"));
	Texture diceTexture = ResourceManager::GetTexture("dice");
	Texture dirtTexture = ResourceManager::GetTexture("dirt");
	Texture containerTexture = ResourceManager::GetTexture("container");

	ChunkMeshBuilder chunkBuilder;

	Mesh chunkMesh;
	chunkBuilder.BuildChunkMesh(&chunkMesh);

	chunkRenderer = new ChunkRenderer();
	chunkRenderer->AddChunk(new Chunk(chunkMesh));
}


void Game::Update(float deltaTime)
{

}


void Game::Render()
{
	chunkRenderer->Render(*camera, ResourceManager::GetShader("cube"));
}

void Game::ProcessInput(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(RIGHT, deltaTime);
	}
}