#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <glew.h>
#include <iostream>
#include "ShaderManager.h"
#include "Shape.h"

class GameWorld
{
public:
	static bool init();
	static void update();
	static void draw();

private:
	GameWorld();
	GameWorld(const GameWorld& gameWorldCopy);
	~GameWorld();

	static GLuint progIndex;
	static GLuint vAO;
	static Shape* triangle;
};

#endif
