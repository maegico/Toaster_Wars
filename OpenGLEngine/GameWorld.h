#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <glew.h>
#include <glm\glm.hpp>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "CameraObject.h"
#include "ShaderManager.h"
#include "Shape.h"
#include "GameObject.h"
#include "ModelLoaderManager.h"

struct modelData
{
	std::string texturePath;
	std::string modelPath;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};

class GameWorld
{
public:
	//static std::vector<glm::vec2> uvs;
	//static std::vector<glm::vec3> normals;

	static bool init();
	static bool update(GLFWwindow* windowPtr);
	static void draw();
	static void keyPress(GLFWwindow* windowPtr, int key, int scancode, int action, int mods);
	static void mouseMove(GLFWwindow* windowPtr, double xpos, double ypos);

private:
	static std::vector<Shape*> shapePtrs;
	static std::vector<GameObject*> gameObjPtrs;
	static CameraObject camera;
	static int numTri;
	static GLuint progIndex;
	static GLuint vAO;
	static float deltaTime;
	static float lastFoV;
	static glm::vec2 lastMousePos;
	static double lastTime;
	static bool quit;

	GameWorld();
	GameWorld(const GameWorld& gameWorldCopy);
	~GameWorld();

	static glm::vec2 getCursorPos(GLFWwindow* windowPtr);
};

#endif
