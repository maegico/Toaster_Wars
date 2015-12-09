#pragma once

#include "Bullet.h"
class Ship
{
public:
	Ship();
	~Ship();

private:
	int health;
	Bullet bullet;
	float time;
	float bulletInterval;

	void setVelocity();
	void Shoot();
	void changeHealth(int damage);
};

