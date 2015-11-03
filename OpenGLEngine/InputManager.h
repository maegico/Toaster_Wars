#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glm\glm.hpp>
#include <glfw3.h>

class InputManager
{
public:
	InputManager();
	InputManager(const InputManager& inputManagerCopy);
	~InputManager();
};

#endif