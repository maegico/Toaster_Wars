#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::getPickup()
{
}

void Player::setVelocity()
{
	if (up)
	{
		velocity = vec3(0, .0005f, 0);
	}
	if (down)
	{
		velocity = vec3(0, -.0005f, 0);
	}
	else
	{
		velocity = vec3(0, 0, 0);
	}
}

void Player::Shoot()
{
	bullets.push_back(Bullet(position));
}

void Player::changeHealth(int damage)
{
	health += damage;
}