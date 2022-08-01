#pragma once
#include "Entity.h"
#include "HeartPickup.h"

class Enemy :
	public Entity
{
public:

	Enemy(Vector2 spawnPosition);
	virtual ~Enemy();
	bool Offscreen();
	void Die();
	int GetDamage() { return damage; }
	static void SetPickupVector(std::vector<Pickup*>* pickups);
protected:

	static std::vector<Pickup*>* pickupVector;
	int damage;
	void DropLoot();
};

