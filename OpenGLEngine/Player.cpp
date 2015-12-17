#include "Player.h"


Player::Player()
{
}

Player::Player(GameObject* _obj, GameObject* b)
{
	obj = _obj;
	bulletPrefab = b;
	up = down = shooting = false;
	time = 0;
}


Player::~Player()
{
}

void Player::getPickup()
{
}

void Player::update(float dt)
{
	time += dt;
	if (up && !down)
	{
		velocity = vec3(0, .5f, 0);
	}
	else if (down && !up)
	{
		velocity = vec3(0, -.5f, 0);
	}
	else if((!down && !up) || (down && up))
	{
		velocity = vec3(0, 0, 0);
	}

	obj->setPosition(obj->getPosition() + (velocity*dt));

	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet b = bullets[i];
		b.update(dt);
		if (b.offScreen())
		{
			bullets.erase(bullets.begin() + i);
		}
	}
	if (shooting && time >= 0.3f)
	{
		time = 0;
		Shoot();
	}
}

void Player::Shoot()
{
	vec3 pos = vec3(obj->getPosition().x + 0.2f, obj->getPosition().y, obj->getPosition().z);
	bullets.push_back(Bullet(new GameObject(bulletPrefab),pos));
}

void Player::changeHealth(int damage)
{
	health += damage;
}