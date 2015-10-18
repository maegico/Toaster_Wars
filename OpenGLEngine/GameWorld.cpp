#include "GameWorld.h"

bool GameWorld::heldDown = false;
int GameWorld::numTri = 0;
GLuint GameWorld::progIndex = -1;
GLuint GameWorld::vAO;
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
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("glew init error \n%s\n", glewGetErrorString(glewError));
		return false;
	}

	//gets the current OpenGl version the graphics card supports and prints it
	const GLubyte* glVersion = glGetString(GL_VERSION);
	std::cout << "OpenGL version: " << glVersion << std::endl;
	//gets the current GLSL version the graphics card supports and prints it
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "GLSL Version: " << glslVersion << std::endl;

	progIndex = ShaderManager::loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (progIndex == 0)
	{
		std::cout << "PROBLEM: progIndex = 0" << std::endl;
		return false;
	}
	
	glUseProgram(progIndex);

	glGenVertexArrays(1, &vAO);
	glBindVertexArray(vAO);

	//a array holding a basic triangle
	//make it's center the origin
	float verts[] = { -0.25f, -0.25f, 0.0f, 0.0f, 1.0f,
					0.0f, 0.25f, 0.0f, 1.0f, 0.0f,
					0.25f, -0.25f, 1.0f, 0.0f, 0.0f };

	for (int i = 0; i < 100; ++i)
	{
		shapePtrs.push_back(new Shape(verts, 3, progIndex));
	}

	//background color (It's a very ugly color)
	glClearColor(0.5f, 0.75f, 0.5f, 1.0f);

	return true;
}

void GameWorld::update(GLFWwindow* windowPtr)
{
	int currentTime = (int)(glfwGetTime() * 1000);

	float velX = (((float)(rand() % 200) / 100) - 1.0f) / 100;
	float velY = (((float)(rand() % 200) / 100) - 1.0f) / 100;

	float rotAngle = ((float)(rand() % 100) / 100000);

	numTri = gameObjPtrs.size();
	
	if (heldDown == true && gameObjPtrs.size() < 100)
		gameObjPtrs.push_back(new GameObject(shapePtrs[numTri], glm::vec3(getCursorPos(windowPtr), 0.0f), glm::vec3(velX, velY, 0.0f), 0.2f, glm::vec3(0.0f, 0.0f, 1.0f), rotAngle, glm::vec3(1.0f, 1.0f, 1.0f)));//scale:0.2f

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