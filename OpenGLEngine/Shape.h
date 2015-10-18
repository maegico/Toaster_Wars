#ifndef SHAPE_H
#define SHAPE_H

#include <glew.h>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
//will probably change this class later on
	//want the interaction with the graphical pipeline in another class
	//shape should be just that a shape

class Shape
{
public:
	Shape();
	Shape(GLfloat verts[], int numVert, GLuint progIndex);
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
	int numVert;
	GLuint progIndex;
	GLuint uniformColorLoc;
	GLuint uniformMatrixLoc;
};

#endif