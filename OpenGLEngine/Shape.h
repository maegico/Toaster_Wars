#ifndef SHAPE_H
#define SHAPE_H

#include "MatrixData.h"
#include <glew.h>
#include <iostream>
#include <vector>
#include <SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
//will probably change this class later on
	//want the interaction with the graphical pipeline in another class
	//shape should be just that a shape

class Shape
{
public:
	Shape();
	Shape(std::vector<glm::vec3> verts, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, GLuint progIndex);
	Shape(const Shape& shapeCopy);
	~Shape();

	void draw(modelMatrixData mmData, viewMatrixData vmData, windowData wndData, float fov, glm::vec3 color, GLenum drawType);
	
private:
	//vertex buffer object
	//exchange data with GPU with Vertex buffer objects
	GLuint vBO;
	//vertex array object
	//exchange data with GPU about where the vertex buffer objects are
	//with vertex array objects
	GLuint vAO;
	int numVerts;
	GLuint progIndex;
	GLuint uniformColorLoc;
	GLuint uniformModelMatrixLoc;
	GLuint uniformViewMatrixLoc;
	GLuint uniformProjectionMatrixLoc;
};

#endif