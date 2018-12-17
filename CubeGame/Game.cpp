#include "Game.h"
#include "ResourceManager.h"
#include "World/Chunk/ChunkMeshBuilder.h"
#include "World/Chunk/ChunkRenderer.h"
#include "World/Chunk/Chunk.h"
#include "World/Terrain/TerrainGenerator.h"
#include "World/WorldController.h"
#include "Util/GLUtil.h"

#include <GLFW\glfw3.h>

TerrainGenerator* terrainGenerator;
ChunkRenderer* chunkRenderer;
WorldController* worldController;


Game::Game()
{

}

Game::~Game()
{
	gameRunning = false;
	for (auto& thread : chunkLoadThreads)
	{
		thread.join();
	}

	delete chunkRenderer;
	delete terrainGenerator;
	delete worldController;
}

void Game::SetWindow(GLFWwindow* _window)
{
	this->window = _window;
}

void Game::SetCamera(Camera* _camera)
{
	this->camera = _camera;
}

void Game::Update()
{
	glfwMakeContextCurrent(window);
	while (gameRunning)
	{
		worldController->Update();
	}
}

void Game::Init()
{
	gameRunning = true;

	ResourceManager::LoadShader("Resources/Shaders/Chunk.vs", "Resources/Shaders/Chunk.fs", nullptr, "chunk");
	ResourceManager::LoadTexture("Resources/Textures/container.jpg", false, "container");
	ResourceManager::LoadTexture("Resources/Textures/dice_texture.png", false, "dice");
	ResourceManager::LoadTexture("Resources/Textures/dirt.png", false, "dirt");
	ResourceManager::LoadTexture("Resources/Textures/TextureAtlas.png", false, "TextureAtlas");

	Texture diceTexture = ResourceManager::GetTexture("dice");
	Texture dirtTexture = ResourceManager::GetTexture("dirt");
	Texture containerTexture = ResourceManager::GetTexture("container");

	chunkRenderer = new ChunkRenderer();
	terrainGenerator = new TerrainGenerator();
	worldController = new WorldController(terrainGenerator, camera, chunkRenderer);

	const int numThreads = 1;
	for (int i = 0; i < numThreads; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		chunkLoadThreads.emplace_back([&]()
		{
			Update();
		});
	}
}

void Game::Render()
{
	chunkRenderer->Render(camera, &ResourceManager::GetShader("chunk"));
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