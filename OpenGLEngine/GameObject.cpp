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
	mmData.position = position;
}
glm::vec3 GameObject::getPosition()
{
	return mmData.position;
}
void GameObject::setViewMatrixData(glm::vec3 position, glm::vec3 oneAhead, glm::vec3 up)
{
	vmData.position = position;
	vmData.oneAhead = oneAhead;
	vmData.up = up;
}


GameObject::GameObject()
{
	this->thresholdVel = 0.000005f;
	this->rad = 0.25f;
	this->shapePtr = NULL;
	mmData.position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	mmData.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	mmData.rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
	mmData.rotationAngle = 0.0f;
	fov = 45.0f;
	this->color = glm::vec3(0.0f, 0.0f, 0.0f);
	wndData.width = 400;
	wndData.height = 300;
}

GameObject::GameObject(Shape* shapePtr, glm::vec3 position, glm::vec3 velocity, float scale, glm::vec3 rotationAxis, float rotationAngle, float fov, glm::vec3 color)
{
	this->thresholdVel = 0.0005f;
	this->rad = 0.25f;
	this->shapePtr = shapePtr;
	mmData.position = position;
	this->velocity = velocity;
	mmData.scale = glm::vec3(scale, scale, scale);
	mmData.rotationAxis = rotationAxis;
	mmData.rotationAngle = rotationAngle;
	this->fov = fov;
	this->color = color;
	wndData.width = 400;
	wndData.height = 300;
}

GameObject::GameObject(const GameObject& gameObjectCopy)
{
}

GameObject::~GameObject()
{
}


void GameObject::update(windowData wndData)
{
	mmData.rotationAngle = 0.3f;

	this->wndData = wndData;
	/*
	//change currentTime to a rotVelocity
	//rotationAngle += ((float) (rand() % 10)) / 100;
	rotationAngle += 0.003f;

	glm::vec2 vec2Vel = glm::vec2(velocity.x, velocity.y);

	velocity *= 0.99;

	position += velocity;

	if (velocity.y > -1.0f)
		velocity.y -= 0.0005f;

	if (position.x + 0.1 > 1.0f || position.x - 0.1 > 1.0f)
		velocity = glm::vec3(-1 * velocity.x, velocity.y, velocity.z);
	if (position.x + 0.1 < -1.0f || position.x - 0.1 < -1.0f)
		velocity = glm::vec3(-1 * velocity.x, velocity.y, velocity.z);
	if (position.y + 0.1 > 1.0f || position.y - 0.1 > 1.0f)
		velocity = glm::vec3(velocity.x, -1 * velocity.y, velocity.z);
	if (position.y + 0.1 < -1.0f || position.y - 0.1 < -1.0f)
		velocity = glm::vec3(velocity.x, -1 * velocity.y, velocity.z);
	*/
}

void GameObject::draw(GLenum drawType)
{
	shapePtr->draw(mmData, vmData, wndData, fov, color, drawType);
}
