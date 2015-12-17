#pragma once
#include "Ship.h"
#include "GameObject.h"
class Player :
	public Ship
{
public:
	Player();
	Player(GameObject* _obj, GameObject* b);
	~Player();
	void update(float dt);
	void changeHealth(int damage);
	bool up;
	bool down;
	bool shooting;
	float time;

private:
	void getPickup();
	void Shoot();
	GameObject* obj;
};