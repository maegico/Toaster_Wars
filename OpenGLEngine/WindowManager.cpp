#include "WindowManager.h"

GLFWwindow* WindowManager::windowPtr = nullptr;

WindowManager::WindowManager()
{
}

WindowManager::WindowManager(const WindowManager& windowManagerCopy)
{
}

WindowManager::~WindowManager()
{
}

int WindowManager::init(void)
{

	//Code source: http://www.glfw.org/documentation.html

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	windowPtr = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(windowPtr);

	//glfwSetMouseButtonCallback(windowPtr, GameWorld::mouseClick);

	if (!GameWorld::init())
	{
		glfwTerminate();
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowPtr))
	{

		GameWorld::update(windowPtr);
		GameWorld::draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowPtr);

		/* Poll for and process window events */
		glfwPollEvents();
	}

	glfwDestroyWindow(windowPtr);

	glfwTerminate();

	return 0;
}