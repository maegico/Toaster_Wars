#include "Bullet.h"


Bullet::Bullet()
{
	position = vec3(0, 0, 0);
	velocity = vec3(0.005f, 0.0f, 0.0f);
}

Bullet::Bullet(vec3 pos)
{
	position = pos;
	velocity = vec3(0.005f, 0.0f, 0.0f);
}


Bullet::~Bullet()
{
}

void Bullet::setVelocity()
{
}
