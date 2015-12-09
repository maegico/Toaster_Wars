#pragma once
#include "Ship.h"
class Player :
	public Ship
{
public:
	Player();
	~Player();

private:
	void getPickup();
};