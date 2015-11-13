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

	glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(windowPtr, GameWorld::keyPress);
	glfwSetCursorPosCallback(windowPtr, GameWorld::mouseMove);

	if (!GameWorld::init())
	{
		glfwTerminate();
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowPtr))
	{

		if (GameWorld::update(windowPtr) == true)
			break;
		GameWorld::draw();

		/* Swap front and ba ck buffers */
		glfwSwapBuffers(windowPtr);

		/* Poll for and process window events */
		glfwPollEvents();
	}

	glfwDestroyWindow(windowPtr);

	glfwTerminate();

	return 0;
}