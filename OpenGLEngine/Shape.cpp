#include "Shape.h"


Shape::Shape()
{
	numVert = 0;
	progIndex = NULL;
}

Shape::Shape(const Shape& shapeCopy)
{
}

Shape::Shape(GLfloat verts[], int numVert, GLuint progIndex)
{
	this->numVert = numVert;
	this->progIndex = progIndex;

	//does it matter if this uses the parameter progIndex
	uniformColorLoc = glGetUniformLocation(progIndex, "uniformColor");
	uniformMatrixLoc = glGetUniformLocation(progIndex, "worldMatrix");

	//create one Vertex Array object name and save it in vAO
	glGenVertexArrays(1, &vAO);
	//binds the vertex array with the name saved in vAO
	glBindVertexArray(vAO);

	//creates n number of buffer objects and saves them to the second parameter(which is an array)
	glGenBuffers(1, &vBO);
	//specifies to bind a GL_ARRAY_BUFFER(vertex attributes) to vBO
	glBindBuffer(GL_ARRAY_BUFFER, vBO);
	//creates a new data store and deletes any pre-existing data store
		//Parameters: (type of buffer, size of buffer in bytes,
			//a pointer to the data to store, usage of the data)
		//GL_STATIC_DRAW -the contents will be changed once and used a lot
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVert * 5, verts, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 5, 0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 5, (void*)(sizeof(GL_FLOAT) * 2));

	//enables two generic vertex attribute arrays at index n(the parameter)
	//for position data
	glEnableVertexAttribArray(0);
	//for color data
	glEnableVertexAttribArray(1);
	//define arrays of generic vertex data
	//Parameters(array index, number of values, data type of values, normalized,
	//size of total, offset in bytes)
}

Shape::~Shape()
{
	glDeleteVertexArrays(1, &vAO);
	glDeleteBuffers(1, &vBO);
}

void Shape::draw(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, GLenum drawType)
{
	glm::mat4 worldMatrix = glm::translate(position) * glm::scale(scale) * glm::rotate(rotationAngle, rotationAxis);

	glProgramUniformMatrix4fv(progIndex, uniformMatrixLoc, 1, GL_FALSE, &worldMatrix[0][0]);
	glProgramUniform4f(progIndex, uniformColorLoc, color.r, color.g, color.b, 1.0f);

	//not sure why we rebind the vertex array
	glBindVertexArray(vAO);

	glDrawArrays(drawType, 0, numVert);
}