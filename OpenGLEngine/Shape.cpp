#include "Shape.h"


Shape::Shape()
{
	numVert = 0;
	progIndex = NULL;
}

Shape::Shape(const Shape& shapeCopy)
{
}

//check element's values
Shape::Shape(std::vector<glm::vec3> verts, int numVert, std::vector<GLushort> elements, int numElements, GLuint progIndex)
{
	this->numVert = numVert;
	this->numElements = numElements;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVert * 3, &(verts[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements*sizeof(GLushort), &(elements[0]), GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//enables two generic vertex attribute arrays at index n(the parameter)
	//for position data
	glEnableVertexAttribArray(0);

	//getting texture data into texture sampler
		//need to change the texture
	//GLuint texID = SOIL_load_OGL_texture("image.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//glBindTexture(GL_TEXTURE_2D, texID);

	//getting texture coordinate data off the buffer
		//need to change floats per vert
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * floatsPerVert, (void*)(sizeof(GL_FLOAT) * 3);
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE sizeof(GL_FLOAT) * floatsPerVert, 0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * floatsPerVert, (void*)(sizeof(GL_FLOAT) * 5);
	//glEnableVertexAttribArray(2);
}

Shape::~Shape()
{
	//check if we need to delete element buffer
	glDeleteVertexArrays(1, &vAO);
	glDeleteBuffers(1, &vBO);
}

void Shape::draw(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color, GLenum drawType)
{
	glm::mat4 worldMatrix = glm::translate(position) * glm::scale(scale) * glm::rotate(rotationAngle, rotationAxis);

	glProgramUniformMatrix4fv(progIndex, uniformMatrixLoc, 1, GL_FALSE, &worldMatrix[0][0]);
	glProgramUniform4f(progIndex, uniformColorLoc, color.r, color.g, color.b, 1.0f);


	//glBindVertexArray(vAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glDrawElements(drawType, numElements, GL_UNSIGNED_SHORT, (void*)0);
}