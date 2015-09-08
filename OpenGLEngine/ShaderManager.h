#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glew.h>
#include <glm\glm.hpp>
#include <iostream>
#include <fstream>

class ShaderManager
{
public:
	//loads a text file and returns char* of the file
	static char* loadTextFile(const char* file);
	//creates and compiles the file read in from loadTextFile into a shader
		//returns the shader's index
	static GLuint loadShader(const char* file, GLenum shaderType);
	//reads in a vertex and fragment shader
	static GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
	static void setShaderColor(GLuint progIndex, const char* uniformColor, float r, float g, float b);

private:
	ShaderManager();
	ShaderManager(const ShaderManager& shaderManagerCopy);
	~ShaderManager();
};

#endif