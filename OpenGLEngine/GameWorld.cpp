#include "GameWorld.h"

GLuint GameWorld::progIndex = -1;
GLuint GameWorld::vAO;
Shape* GameWorld::triangle;

GameWorld::GameWorld()
{
}

GameWorld::GameWorld(const GameWorld& gameWorldCopy)
{
}

GameWorld::~GameWorld()
{
	delete triangle;
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

#pragma region Look at Later
	/*	Will play around with these later
	//will occulled objects behind othe objects
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//will allow for transperancy
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(3);
	*/

	//heard about these and could be a useful check later on
	/*
	Non Mac vertex array object
	if(GLEW_ARB_vertex_array_object)
	cout << "genVertexArrays supported" << endl;
	Mac vertex array object
	if(GLEW_APPLE_vertex_array_object)
	cout << "genVertexArrayAPPLE supported" << endl;
	*/
#pragma endregion

	progIndex = ShaderManager::loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (progIndex == 0)
	{
		std::cout << "PROBLEM: progIndex = 0" << std::endl;
		return false;
	}
	
	glUseProgram(progIndex);

	glGenVertexArrays(1, &vAO);
	glBindVertexArray(vAO);

	//create triangle here
	float verts[] = { -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
					1.0f, 0.0f, 1.0f, 0.0f, 0.0f };

	triangle = new Shape(verts, 3, progIndex);

	//background color
	glClearColor(0, 1, 0, 1);

	return true;
}

void GameWorld::update()
{
	//nothing right now
}

void GameWorld::draw()
{
	//clears the buffer currently enabled for color writing
	glClear(GL_COLOR_BUFFER_BIT);

	ShaderManager::setShaderColor(progIndex, "color", 1.0f, 1.0f, 1.0f);
	
	triangle->draw(GL_TRIANGLE_FAN);

	glFlush();
}
