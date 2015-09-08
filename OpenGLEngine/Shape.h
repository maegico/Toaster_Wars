#ifndef SHAPE_H
#define SHAPE_H

#include <glew.h>
#include <iostream>
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

	void draw(GLenum drawType);
	
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
};

#endif