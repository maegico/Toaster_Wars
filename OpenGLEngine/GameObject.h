#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/*Might want to change it to having it inherit Shape
	instead of take it in and holding an instance of it
		Looking to reduce the amount of memory on the heap
		also note sure why we need to have twice as many objects on the heap*/

#include "MatrixData.h"
#include "Shape.h"
#include "Collider3D.h"
#include <glm\glm.hpp>

class GameObject
{
public:
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setVelocity(glm::vec3 velocity);
	glm::vec3 getVelocity();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setViewMatrixData(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

	Collider3D* colliderPtr;

	GameObject();
	GameObject(Shape* shapePtr, glm::vec3 position, glm::vec3 velocity, float scale, glm::vec3 rotationAxis, float rotationAngle, float fov, glm::vec3 color);
	GameObject(const GameObject& gameObjectCopy);
	~GameObject();

	void update(windowData wndData);
	void draw(GLenum drawType);

private:
	float thresholdVel;
	float rad;
	float fov;
	Shape* shapePtr;
	modelMatrixData mmData;
	viewMatrixData vmData;
	windowData wndData;
	glm::vec3 velocity, color;
};

#endif