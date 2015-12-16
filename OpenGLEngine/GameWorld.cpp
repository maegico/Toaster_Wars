#include "GameWorld.h"

std::vector<Shape*> GameWorld::shapePtrs = std::vector<Shape*>(0);
std::vector<GameObject*> GameWorld::gameObjPtrs = std::vector<GameObject*>(0);
CameraObject GameWorld::camera = CameraObject();
int GameWorld::numTri = 0;
GLuint GameWorld::progIndex = -1;
GLuint GameWorld::vAO;
float GameWorld::deltaTime = 0.0f;
float GameWorld::lastFoV = 0.0f;
glm::vec2 GameWorld::lastMousePos = glm::vec2(0, 0);
double GameWorld::lastTime = 0;
bool GameWorld::quit = false;
bool camUp = false;
bool camDown = false;
bool camRight = false;
bool camLeft = false;
bool camForward = false;
bool camBack = false;

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

	glClearColor(0.5f, 0.75f, 0.5f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	progIndex = ShaderManager::loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (progIndex == 0)
	{
		std::cout << "PROBLEM: progIndex = 0" << std::endl;
		return false;
	}
	
	glUseProgram(progIndex);

	glGenVertexArrays(1, &vAO);
	glBindVertexArray(vAO);

	modelData model1 = { "Textures/default.png", "Models/cube.obj", std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };


	if (!ModelLoaderManager::loadObj(model1.modelPath, model1.verts, model1.uvs, model1.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}


	for (int i = 0; i < 1; ++i)
	{
		shapePtrs.push_back(new Shape(model1.verts, model1.uvs, model1.normals, model1.texturePath.c_str(), progIndex));
	}

	glm::vec3 threeDZero = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 twoDZero = glm::vec2(0.0f, 0.0f);

	gameObjPtrs.push_back(new GameObject(shapePtrs[gameObjPtrs.size()], threeDZero, threeDZero, 0.25f, glm::vec3(1, 1, 0), 0, camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f)));
	
	return true;
}

bool GameWorld::update(GLFWwindow* windowPtr)
{
	for (int i = 0; i < gameObjPtrs.size(); ++i)
	{
		gameObjPtrs[i]->setViewMatrixData(camera.getLocation(), camera.getOneAhead(), camera.getUp());
	}

	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	windowData wndData;
	glfwGetWindowSize(windowPtr, &(wndData.width), &(wndData.height));
	//to voom out and in - glfwGetMouseWheel() is depricated
	//camera.setFoV = lastFoV - 5 * glfwGetMouseWheel();

	for (int i = 0; i < gameObjPtrs.size(); ++i)
	{
		gameObjPtrs[i]->update(wndData);
	}

	if (camUp)
		camera.position += camera.getUp() * deltaTime * camera.speed;
	if (camDown)
		camera.position -= camera.getUp() * deltaTime * camera.speed;
	if (camLeft)
		camera.position -= camera.getRight() * deltaTime * camera.speed;
	if (camRight)
		camera.position += camera.getRight() * deltaTime * camera.speed;
	if (camForward)
		camera.position += camera.getForward() * deltaTime * camera.speed;
	if (camBack)
		camera.position -= camera.getForward() * deltaTime * camera.speed;

	lastTime = currentTime;

	return quit;
}

void GameWorld::draw()
{
	//clears the buffer currently enabled for color writing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw here
	for (int i = 0; i < gameObjPtrs.size(); i++)
	{
		gameObjPtrs[i]->draw(GL_TRIANGLES);
	}

	glFlush();
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

void GameWorld::keyPress(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_PRESS)
		camUp = true;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_PRESS)
		camDown = true;
	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && action == GLFW_PRESS)
		camLeft = true;
	if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && action == GLFW_PRESS)
		camRight = true;
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_RELEASE)
		camUp = false;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_RELEASE)
		camDown = false;
	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && action == GLFW_RELEASE)
		camLeft = false;
	if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && action == GLFW_RELEASE)
		camRight = false;
	//move forward
	if ((key == GLFW_KEY_Z || key == GLFW_KEY_R) && action == GLFW_PRESS)
		camForward = true;
	if ((key == GLFW_KEY_Z || key == GLFW_KEY_R) && action == GLFW_RELEASE)
		camForward = false;
	//move backward
	if ((key == GLFW_KEY_X || key == GLFW_KEY_F) && action == GLFW_PRESS)
		camBack = true;
	if ((key == GLFW_KEY_X || key == GLFW_KEY_F) && action == GLFW_RELEASE)
		camBack = false;
	if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS)
		quit = true;
}
void GameWorld::mouseMove(GLFWwindow* windowPtr, double xpos, double ypos)
{
	camera.turn((xpos - lastMousePos.x)/1000, (ypos - lastMousePos.y)/1000);

	lastMousePos.x = xpos;
	lastMousePos.y = ypos;
}

