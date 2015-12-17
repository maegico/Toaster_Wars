#pragma once
#include "Ship.h"
#include "GameObject.h"
#include "OctTree.h"
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
	bool powerup;
	float powerUpTimer;
	bool playing;

private:
	void getPickup();
	void Shoot();
	GameObject* obj;
};