#include "GameObject.h"

void GameObject::setColor(glm::vec3 color)
{
	this->color = color;
}
glm::vec3 GameObject::getColor()
{
	return color;
}
void GameObject::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}
glm::vec3 GameObject::getVelocity()
{
	return velocity;
}
void GameObject::setPosition(glm::vec3 position)
{
	this->position = position;
}
glm::vec3 GameObject::getPosition()
{
	return position;
}


GameObject::GameObject()
{
	this->thresholdVel = 0.000005f;
	this->rad = 0.25f;
	this->shapePtr = NULL;
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = 1.0f;
	this->rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotationAngle = 0.0f;
	this->color = glm::vec3(0.0f, 0.0f, 0.0f);
}

GameObject::GameObject(Shape* shapePtr, glm::vec3 position, glm::vec3 velocity, float scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 color)
{
	this->thresholdVel = 0.0005f;
	this->rad = 0.25f;
	this->shapePtr = shapePtr;
	this->position = position;
	this->velocity = velocity;
	this->scale = scale;
	this->rotationAxis = rotationAxis;
	this->rotationAngle = rotationAngle;
	this->color = color;
}

GameObject::GameObject(const GameObject& gameObjectCopy)
{
}

GameObject::~GameObject()
{
}


void GameObject::update()
{
	//change currentTime to a rotVelocity
	rotationAngle += ((float) (rand() % 10)) / 100;

	glm::vec2 vec2Vel = glm::vec2(velocity.x, velocity.y);

	velocity *= 0.99;

	position += velocity;

	if (velocity.y > -1.0f)
		velocity.y -= 0.0005f;

	if (position.x + 0.05 > 1.0f || position.x - 0.05 > 1.0f)
		velocity = glm::vec3(-1 * velocity.x, velocity.y, velocity.z);
	if (position.x + 0.05 < -1.0f || position.x - 0.05 < -1.0f)
		velocity = glm::vec3(-1 * velocity.x, velocity.y, velocity.z);
	if (position.y + 0.05 > 1.0f || position.y - 0.05 > 1.0f)
		velocity = glm::vec3(velocity.x, -1 * velocity.y, velocity.z);
	if (position.y + 0.05 < -1.0f || position.y - 0.05 < -1.0f)
		velocity = glm::vec3(velocity.x, -1 * velocity.y, velocity.z);
}

void GameObject::draw(GLenum drawType)
{
	shapePtr->draw(position, glm::vec3(scale, scale, scale), rotationAxis, rotationAngle, color, drawType);
}
