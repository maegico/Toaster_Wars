#ifndef COLLIDER3D_H
#define COLLIDER3D_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <glm\glm.hpp>
class Collider3D
{
public:
	// Center and half-width.
	glm::vec3 c, e;
	glm::vec3 u[3];

	void print();
	bool collidesWith(Collider3D* colliderPtr);
	Collider3D(glm::vec3 c, glm::vec3 e);

	Collider3D();
	~Collider3D();
};

#endif