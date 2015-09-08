#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "GameWorld.h"

class WindowManager
{
public:
	static int init();
	static GLFWwindow* windowPtr;
	static GameWorld* gameWorldPtr;

private:
	WindowManager();
	WindowManager(const WindowManager& windowManagerCopy);
	~WindowManager();
};

#endif