#ifndef MATRIXDATA_H
#define MATRIXDATA_H

#include <glm\glm.hpp>

struct modelMatrixData
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float rotationAngle;
};

struct viewMatrixData
{
	glm::vec3 position;
	glm::vec3 oneAhead;
	glm::vec3 up;
};

struct windowData
{
	int width;
	int height;
};

#endif