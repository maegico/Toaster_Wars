#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy(GameObject * pb, GameObject * hlth, vec3 location, GameObject* _obj, GameObject* b)
{
	obj = _obj;
	pickup = pb;
	healthP = hlth;
	obj->setPosition(location);
	bulletPrefab = b;
	time = 0;
	health = 3;
}


Enemy::~Enemy()
{
}

void Enemy::draw()
{
	obj->draw(GL_TRIANGLES);
}

void Enemy::Shoot()
{
	vec3 pos = vec3(obj->getPosition().x - 0.1f, obj->getPosition().y, obj->getPosition().z);
	bullets.push_back(Bullet(new GameObject(bulletPrefab), pos));
	bullets.back().setVelocity(vec3(-0.5f, 0.0f, 0.0f));
	bullets.back().setAngle((3.1415 / 2));
}

void Enemy::update(float dt)
{
	time += dt;
	obj->setPosition(obj->getPosition() + (obj->getVelocity() * dt));
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet b = bullets[i];
		b.update(dt);
		if (b.getPosition().x <= -1)
		{
			//bullets.erase(bullets.begin() + i);
		}
	}
	if (time >= 1.f)
	{
		time = 0;
		Shoot();
	}
}

bool Enemy::changeHealth(int damage, bool x)
{
	health += damage;
	if (health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::changeHealth(int damage)
{
}

void Enemy::setViewMatrixData(glm::vec3 position, glm::vec3 oneAhead, glm::vec3 up)
{
	obj->setViewMatrixData(position, oneAhead, up);
	for each(Bullet b in bullets)
	{
		b.setViewMatrixData(position, oneAhead, up);
	}
}

Collider3D * Enemy::getCollider()
{
	return obj->colliderPtr;
}

GameObject * Enemy::getOBJ()
{
	return obj;
}
