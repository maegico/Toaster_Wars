#pragma once
#include "Ship.h"
class Enemy :
	public Ship
{
public:
	Enemy();
	~Enemy();

private:
	void dropPickup();
};

