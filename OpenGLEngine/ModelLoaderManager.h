#ifndef  MODELLOADERMANAGER_H
#define MODELLOADERMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glew.h>
#include <glm\glm.hpp>

class ModelLoaderManager
{
public:
	//reads a file and writes out the data
		//returns false if it fails
	static bool loadObj(std::string path, std::vector<glm::vec3> &vertices, std::vector<GLushort> &elements);

private:
	ModelLoaderManager();
	ModelLoaderManager(const ModelLoaderManager& modelLoaderManagerCopy);
	~ModelLoaderManager();
};

#endif

