#include "Application.h"
#include "ResourceManager.h"
#include "Util/GLUtil.h"


Application::Application()
{
	SetUp();
	
	camera = new Camera(glm::vec3(8.0f, 20.0f, 8.0f));
	game.SetCamera(camera);
	game.SetWindow(window);
}

Application::~Application()
{
	ResourceManager::Clear();
	glfwTerminate();

	delete camera;
}

void Application::Start()
{
	game.Init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Process input
		game.ProcessInput(deltaTime);
		//game.Update();

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		game.Render();

		//CheckOpenGLError();
		glfwSwapBuffers(window);
	}
}

// Initializes all openGL functions and creates window
void Application::SetUp()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CubeGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Capture mouse movements
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, this->KeyCallback);
	glfwSetFramebufferSizeCallback(window, this->FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, this->MouseCallback);
	glfwSetScrollCallback(window, this->ScrollCallback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	// OpenGL configuration
	glEnable(GL_DEPTH_TEST);

	// Face culling options
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

// Callback for key presses
void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

}

// Callback for mouse movement
void Application::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));

	if (app->firstMouse)
	{
		app->lastX = xpos;
		app->lastY = ypos;
		app->firstMouse = false;
	}

	float xoffset = xpos - app->lastX;
	float yoffset = app->lastY - ypos; // reversed since y-coordinates go from bottom to top

	app->lastX = xpos;
	app->lastY = ypos;

	app->camera->ProcessMouseMovement(xoffset, yoffset);
}

// Called on window size change by either OS or user
void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// Callback for scroll 
void Application::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	void* data = glfwGetWindowUserPointer(window);
	Application *app = static_cast<Application *>(data);
	app->camera->ProcessMouseScroll(yoffset);
}


