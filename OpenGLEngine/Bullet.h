#pragma once

#include <iostream>
#include <vector>
#include <glm\glm.hpp>
#include "GameObject.h"

using namespace std;
using namespace glm;
class Bullet
{
public:
	Bullet();
	Bullet(GameObject* _obj, vec3 pos);
	~Bullet();
	void update(float dt);
	void draw();
	void setViewMatrixData(glm::vec3 position, glm::vec3 oneAhead, glm::vec3 up);
	bool offScreen();
	vec3 getPosition();

private:
	vec3 position;
	vec3 velocity;
	int damage;
	GameObject* obj;
};

