#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>
#include <mutex>
#include <atomic>
#include <thread>


class Game
{
public:
	Game();
	~Game();

	// Init game data
	void Init();

	// Main game loop functions
	void Update();
	void Render();
	void ProcessInput(float deltaTime);

	void SetWindow(GLFWwindow* _window);
	void SetCamera(Camera* camera);

private:
	Camera* camera;
	GLFWwindow* window;

	std::atomic<bool> gameRunning { true };
	std::vector<std::thread> chunkLoadThreads;
};