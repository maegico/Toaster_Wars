#pragma once
#include "Ship.h"
class Player :
	public Ship
{
public:
	Player();
	~Player();
	bool up;
	bool down;

private:
	void getPickup();
	void setVelocity();
	void Shoot();
	void changeHealth(int damage);
};