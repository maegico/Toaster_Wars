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

void GameObject::setAngle(float ang)
{
	mmData.rotationAngle = ang;
}



GameObject::GameObject()
{
	this->thresholdVel = 0.000005f;
	this->rad = 0.25f;
	this->colliderPtr = nullptr;
	this->shapePtr = nullptr;
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

	glm::vec3 minOBB = shapePtr->verts[0];
	glm::vec3 maxOBB = shapePtr->verts[0];

	for (glm::vec3 vert : shapePtr->verts)
	{
		glm::vec3 vertN = vert * mmData.scale;
		if (vertN.x < minOBB.x)
			minOBB.x = vertN.x;
		else if (vertN.x > maxOBB.x)
			maxOBB.x = vertN.x;

		if (vertN.y < minOBB.y)
			minOBB.y = vertN.y;
		else if (vertN.y > maxOBB.y)
			maxOBB.y = vertN.y;

		if (vertN.z < minOBB.z)
			minOBB.z = vertN.z;
		else if (vertN.z > maxOBB.z)
			maxOBB.z = vertN.z;
	}

	this->colliderPtr = new Collider3D((maxOBB + minOBB) * 0.5f, (maxOBB - minOBB) * 0.5f);
}

GameObject::GameObject(const GameObject& gameObjectCopy)
{
}

Shape* GameObject::getShapePtr()
{
	return shapePtr;
}

glm::vec3 GameObject::getScale()
{
	return mmData.scale;
}

glm::vec3 GameObject::getAxis()
{
	return mmData.rotationAxis;
}

float GameObject::getAngle()
{
	return mmData.rotationAngle;
}

GameObject::GameObject(GameObject *&gameObjectCopy)
{
	this->thresholdVel = 0.0005f;
	this->rad = 0.25f;
	shapePtr = gameObjectCopy->getShapePtr();
	mmData.position = gameObjectCopy->getPosition();
	velocity = gameObjectCopy->getVelocity();
	mmData.scale = gameObjectCopy->getScale();
	mmData.rotationAxis = gameObjectCopy->getAxis();
	mmData.rotationAngle = gameObjectCopy->getAngle();
	fov = gameObjectCopy->fov;
	color = gameObjectCopy->color;
	wndData.width = 400;
	wndData.height = 300;
	colliderPtr = gameObjectCopy->colliderPtr;
}

GameObject::~GameObject()
{
	if (colliderPtr != nullptr)
		delete colliderPtr;
}

glm::vec3 halfpoint(glm::vec3 vec1, glm::vec3 vec2)
{
	return (vec2 - vec1) * 0.5f;
}

void GameObject::update(windowData wndData)
{
	//mmData.rotationAngle = 0.3f;

	/*glm::vec3 minOBB = shapePtr->verts[0];
	glm::vec3 maxOBB = shapePtr->verts[0];

	for (glm::vec3 vert : shapePtr->verts)
	{
		glm::vec3 vertN = vert * mmData.scale;
		if (vertN.x < minOBB.x)
			minOBB.x = vertN.x;
		else if (vertN.x > maxOBB.x)
			maxOBB.x = vertN.x;

		if (vertN.y < minOBB.y)
			minOBB.y = vertN.y;
		else if (vertN.y > maxOBB.y)
			maxOBB.y = vertN.y;

		if (vertN.z < minOBB.z)
			minOBB.z = vertN.z;
		else if (vertN.z > maxOBB.z)
			maxOBB.z = vertN.z;
	}

	this->colliderPtr->c = (maxOBB + minOBB) * 0.5f;
	this->colliderPtr->e = (maxOBB - minOBB) * 0.5f;*/

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
