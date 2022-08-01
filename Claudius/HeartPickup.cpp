#include "HeartPickup.h"

HeartPickup::HeartPickup(Vector2 position) : Pickup(position)
{
	sprite = new Sprite();
	sprite->SetImage(spriteSheet);
	sprite->SetSource(7 * 8, 0, 8, 8);

	SetCollider();
}

Pickup* HeartPickup::GivePlayerPickup()
{
	player->GiveResources(HEALTH, 2);
	return nullptr;
}
