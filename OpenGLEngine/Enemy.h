#pragma once
#include "Ship.h"
#include "OctTree.h"
class Enemy :
	public Ship
{
public:
	Enemy();
	Enemy(GameObject* pb, GameObject* hlth, vec3 location, GameObject* _obj, GameObject* b);
	~Enemy();
	void draw();
	void update(float dt);
	bool changeHealth(int damage, bool x);
	void changeHealth(int damage);
	void setViewMatrixData(glm::vec3 position, glm::vec3 oneAhead, glm::vec3 up);
	Collider3D* getCollider();
	GameObject* getOBJ();

private:
	void Shoot();
	GameObject* pickup;
	GameObject* healthP;
	GameObject* obj;
	float time;
};