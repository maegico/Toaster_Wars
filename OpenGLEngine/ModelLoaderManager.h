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
	//code found on http://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
	static std::vector<std::string> split(const char* str, char c1, char c2);

	//reads a file and writes out the data
		//returns false if it fails
	static bool loadObj(std::string path, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals);

	ModelLoaderManager();
	ModelLoaderManager(const ModelLoaderManager& modelLoaderManagerCopy);
	~ModelLoaderManager();
};

#endif

