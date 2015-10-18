#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/*Might want to change it to having it inherit Shape
	instead of take it in and holding an instance of it
		Looking to reduce the amount of memory on the heap
		also note sure why we need to have twice as many objects on the heap*/

#include "Shape.h"
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

	GameObject();
	GameObject(Shape* shapePtr, glm::vec3 position, glm::vec3 velocity, float scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color);
	GameObject(const GameObject& gameObjectCopy);
	~GameObject();

	void update();
	void draw(GLenum drawType);

private:
	float thresholdVel;
	float rad;
	Shape* shapePtr;
	glm::vec3 position, velocity, rotationAxis, color;
	float scale, rotationAngle;
	
};

#endif