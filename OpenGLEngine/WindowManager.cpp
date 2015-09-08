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

	if (!GameWorld::init())
	{
		glfwTerminate();
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowPtr))
	{

		GameWorld::update();
		GameWorld::draw();

#pragma region How_To_Make_Arsen_Mad
		//How to make Arsen mad
			//use the fixed pipeline (aka what's below)
		/*glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(-1, 0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0, 1, 0);
			glColor3f(0, 0, 1);
			glVertex3f(1, 0, 0);
		glEnd();*/
#pragma endregion Open Up To See

		/* Swap front and back buffers */
		glfwSwapBuffers(windowPtr);

		/* Poll for and process window events */
		glfwPollEvents();
	}

	glfwDestroyWindow(windowPtr);

	glfwTerminate();

	return 0;
}