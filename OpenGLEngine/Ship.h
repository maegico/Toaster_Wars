#pragma once

#include "Bullet.h"
#include <iostream>
#include <vector>
#include <glm\glm.hpp>

using namespace std;
using namespace glm;
class Ship
{
public:
	Ship();
	virtual ~Ship() = 0;

protected:
	int health;
	vector<Bullet> bullets;
	float time;
	float bulletInterval;
	vec3 velocity;
	vec3 position;

	virtual void setVelocity() = 0;
	virtual void Shoot() = 0;
	virtual void changeHealth(int damage) = 0;
};

