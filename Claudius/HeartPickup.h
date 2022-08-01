#pragma once
#include "Item.h"
class HeartPickup :
	public Pickup
{
public:

	HeartPickup(Vector2 position);
	Pickup* GivePlayerPickup();
};

