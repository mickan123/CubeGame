#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Game.h"

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

class Application
{
public:
	Application();
	~Application();
	void Start();
	void SetUp();

	Game game;
	GLFWwindow* window;
	Camera* camera;

	float lastX = (float)SCREEN_WIDTH / 2.0;
	float lastY = (float)SCREEN_HEIGHT / 2.0;
	bool firstMouse = true;
	
private:
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};