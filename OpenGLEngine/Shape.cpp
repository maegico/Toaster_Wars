#include "Shape.h"


Shape::Shape()
{
	numVerts = 0;
	progIndex = NULL;
}

Shape::Shape(const Shape& shapeCopy)
{
}

//check element's values
Shape::Shape(std::vector<glm::vec3> verts, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, const char* texturePath, GLuint progIndex)
{
	this->verts = verts;
	this->numVerts = verts.size();
	this->progIndex = progIndex;

	//does it matter if this uses the parameter progIndex
	uniformColorLoc = glGetUniformLocation(progIndex, "uniformColor");
	uniformModelMatrixLoc = glGetUniformLocation(progIndex, "modelMatrix");
	uniformViewMatrixLoc = glGetUniformLocation(progIndex, "viewMatrix");
	uniformProjectionMatrixLoc = glGetUniformLocation(progIndex, "projectionMatrix");

	int sizeVerts = sizeof(GL_FLOAT) * verts.size() * 3;
	int sizeUVs = sizeof(GL_FLOAT) * uvs.size() * 2;
	int sizeNormals = sizeof(GL_FLOAT) * normals.size() * 3;

	glGenVertexArrays(1, &vAO);
	glGenBuffers(1, &vBO);

	glBindVertexArray(vAO);
	glBindBuffer(GL_ARRAY_BUFFER, vBO);

	glBufferData(GL_ARRAY_BUFFER, sizeVerts + sizeUVs + sizeNormals, 0, GL_STATIC_DRAW);

	//deal with buffer Sub Data
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVerts, &verts[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeVerts, sizeUVs, &uvs[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeVerts + sizeUVs, sizeNormals, &normals[0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeVerts));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeVerts + sizeUVs));

	//getting texture data into texture sampler
	texID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, texID);
}
	

Shape::~Shape()
{
	glDeleteVertexArrays(1, &vAO);
	glDeleteBuffers(1, &vBO);
}

void Shape::draw(modelMatrixData mmData, viewMatrixData vmData, windowData wndData, float fov, glm::vec3 color, GLenum drawType)
{
	glm::mat4 projectionMatrix = glm::perspective(fov, (float)(wndData.width / wndData.height), 0.01f, 1000.0f);
	glm::mat4 viewMatrix = glm::lookAt(vmData. position, vmData.oneAhead, vmData.up);
	glm::mat4 modelMatrix = glm::translate(mmData.position) * glm::scale(mmData.scale) * glm::rotate(mmData.rotationAngle, mmData.rotationAxis);

	glProgramUniformMatrix4fv(progIndex, uniformModelMatrixLoc, 1, GL_FALSE, &modelMatrix[0][0]);
	glProgramUniformMatrix4fv(progIndex, uniformViewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	glProgramUniformMatrix4fv(progIndex, uniformProjectionMatrixLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
	glProgramUniform4f(progIndex, uniformColorLoc, color.r, color.g, color.b, 1.0f);

	glDrawArrays(drawType, 0, numVerts);
}