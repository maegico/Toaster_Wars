#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <glew.h>
#include <glm\glm.hpp>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "ShaderManager.h"
#include "Shape.h"
#include "GameObject.h"

class GameWorld
{
public:
	static bool init();
	static void update(GLFWwindow* windowPtr);
	static void draw();
	static void mouseClick(GLFWwindow* windowPtr, int button, int action, int mods);

private:
	static bool heldDown;
	static int numTri;
	static GLuint progIndex;
	static GLuint vAO;
	static std::vector<Shape*> shapePtrs;
	static std::vector<GameObject*> gameObjPtrs;

	GameWorld();
	GameWorld(const GameWorld& gameWorldCopy);
	~GameWorld();

	static glm::vec2 getCursorPos(GLFWwindow* windowPtr);
};

#endif
