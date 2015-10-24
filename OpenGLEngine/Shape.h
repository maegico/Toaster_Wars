#ifndef SHAPE_H
#define SHAPE_H

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
	Shape(std::vector<glm::vec3> verts, int numVert, std::vector<GLushort> elements, int numElements, GLuint progIndex);
	Shape(const Shape& shapeCopy);
	~Shape();

	void draw(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, GLenum drawType);
	
private:
	//vertex buffer object
	//exchange data with GPU with Vertex buffer objects
	GLuint vBO;
	//vertex array object
	//exchange data with GPU about where the vertex buffer objects are
	//with vertex array objects
	GLuint vAO;
	GLuint elementBuffer;
	int numVert;
	int numElements;
	GLuint progIndex;
	GLuint uniformColorLoc;
	GLuint uniformMatrixLoc;
};

#endif