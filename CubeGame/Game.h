#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>

class Game
{
public:
	Game();
	~Game();

	// Init game data
	void Init();

	// Main game loop functions
	void Update(float deltaTime);
	void Render();
	void ProcessInput(float deltaTime);

	void SetWindow(GLFWwindow* _window);
	void SetCamera(Camera* camera);

private:
	Camera* camera;
	GLFWwindow* window;
};