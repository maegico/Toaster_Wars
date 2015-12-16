#pragma once

#include <iostream>
#include <vector>
#include <glm\glm.hpp>

using namespace std;
using namespace glm;
class Bullet
{
public:
	Bullet();
	Bullet(vec3 pos);
	~Bullet();

private:
	vec3 position;
	vec3 velocity;
	int damage;
	void setVelocity();
};

