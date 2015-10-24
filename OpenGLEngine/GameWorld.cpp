#include "GameWorld.h"

int GameWorld::numTri = 0;
GLuint GameWorld::progIndex = -1;
GLuint GameWorld::vAO;
bool GameWorld::heldDown = false;
std::vector<Shape*> GameWorld::shapePtrs = std::vector<Shape*>(0);
std::vector<GameObject*> GameWorld::gameObjPtrs = std::vector<GameObject*>(0);

GameWorld::GameWorld()
{
}

GameWorld::GameWorld(const GameWorld& gameWorldCopy)
{
}

GameWorld::~GameWorld()
{
	for (int i = 0; i < gameObjPtrs.size(); ++i)
	{
		delete gameObjPtrs[i];
	}
	for (int i = 0; i < shapePtrs.size(); ++i)
	{
		delete shapePtrs[i];
	}
}

bool GameWorld::init()
{
	//allows the use of new features
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		//printf("glew init error \n%s\n", glewGetErrorString(glewError));
		std::cout << "ERROR: GLEW did not initialize." << std::endl;
		return false;
	}

	//glClearColor(0.5f, 0.75f, 0.5f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	progIndex = ShaderManager::loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (progIndex == 0)
	{
		std::cout << "PROBLEM: progIndex = 0" << std::endl;
		return false;
	}
	
	glUseProgram(progIndex);

	glGenVertexArrays(1, &vAO);
	glBindVertexArray(vAO);

	std::vector<glm::vec3> verts;
	std::vector<GLushort> elements;

	if (!ModelLoaderManager::loadObj("Models/cube.obj", verts, elements))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}


	for (int i = 0; i < 1; ++i)
	{
		shapePtrs.push_back(new Shape(verts, verts.size(), elements, elements.size(), progIndex));
	}

	glm::vec3 threeDZero = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 twoDZero = glm::vec2(0.0f, 0.0f);

	gameObjPtrs.push_back(new GameObject(shapePtrs[gameObjPtrs.size()], threeDZero, threeDZero, 1.0f, glm::vec3(1, 1, 0), 0, glm::vec3(1.0f, 0.0f, 0.0f)));

	//background color (It's a very ugly color)
	glClearColor(0.5f, 0.75f, 0.5f, 1.0f);

	return true;
}

void GameWorld::update(GLFWwindow* windowPtr)
{
	for (int i = 0; i < gameObjPtrs.size(); ++i)
	{
		gameObjPtrs[i]->update();
	}
}

void GameWorld::draw()
{
	//clears the buffer currently enabled for color writing
	glClear(GL_COLOR_BUFFER_BIT);

	//draw here
	for (int i = 0; i < gameObjPtrs.size(); i++)
	{
		gameObjPtrs[i]->draw(GL_TRIANGLES);
	}

	glFlush();
}

void GameWorld::mouseClick(GLFWwindow* windowPtr, int button, int action, int mods)
{
	std::cout << "Num Shapes: " << shapePtrs.size() << std::endl;
	std::cout << "Num GameObjs: " << gameObjPtrs.size() << std::endl;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		heldDown = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		heldDown = false;
}

glm::vec2 GameWorld::getCursorPos(GLFWwindow* windowPtr)
{
	double xpos, ypos;
	glm::vec2 cursorPos;
	int width, height;

	glfwGetCursorPos(windowPtr, &xpos, &ypos);

	glfwGetWindowSize(windowPtr, &width, &height);

	cursorPos.x = (((float)xpos / width) * 2) - 1;
	cursorPos.y = -1 * ((((float)ypos / height) * 2) - 1);

	return cursorPos;
}