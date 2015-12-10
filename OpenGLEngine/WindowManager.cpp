#include "WindowManager.h"
#include "StateManager.h"
GLFWwindow* WindowManager::windowPtr = nullptr;


StateManager stateMan;

WindowManager::WindowManager()
{
}

WindowManager::WindowManager(const WindowManager& windowManagerCopy)
{
}

WindowManager::~WindowManager()
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		stateMan.setState(stateMan.GameScreen);
	}
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
	// Check current State
	//if (currentState == GameScreen){

		//}
	bool test = false;

		if (!GameWorld::init())
		{
			glfwTerminate();
			return -1;
		}
	

	// Set a keycallback to change the State
	glfwSetKeyCallback(windowPtr, key_callback);

	stateMan.setState(stateMan.MainMenu);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowPtr))
	{
		// Check current State
		if (stateMan.getState() == stateMan.GameScreen){
			glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetKeyCallback(windowPtr, GameWorld::keyPress);
			glfwSetCursorPosCallback(windowPtr, GameWorld::mouseMove);

		if (GameWorld::update(windowPtr) == true)
			break;
		GameWorld::draw();
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(windowPtr);

		/* Poll for and process window events */
		glfwPollEvents();
	}

	glfwDestroyWindow(windowPtr);

	glfwTerminate();

	return 0;
}