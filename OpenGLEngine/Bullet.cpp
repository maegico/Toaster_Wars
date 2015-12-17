#include "Bullet.h"


Bullet::Bullet()
{
	position = vec3(0, 0, 0);
	velocity = vec3(0.5f, 0.0f, 0.0f);
	damage = 1;
}

Bullet::Bullet(GameObject* _obj, vec3 pos)
{
	obj = _obj;
	obj->setPosition(pos);
	velocity = vec3(0.5f, 0.0f, 0.0f);
	damage = 1;
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	obj->setPosition(obj->getPosition() + (velocity * dt));
}

void Bullet::draw()
{
	obj->draw(GL_TRIANGLES);
}

void Bullet::setViewMatrixData(glm::vec3 position, glm::vec3 oneAhead, glm::vec3 up)
{
	obj->setViewMatrixData(position, oneAhead, up);
}

bool Bullet::offScreen()
{
	if (obj->getPosition().x > 1) return true;
	return false;
}

vec3 Bullet::getPosition()
{
	return obj->getPosition();
}

void Bullet::setVelocity(vec3 vel)
{
	velocity = vel;
}

void Bullet::setAngle(float ang)
{
	obj->setAngle(ang);
}

Collider3D* Bullet::getCollider()
{
	return obj->colliderPtr;
}
