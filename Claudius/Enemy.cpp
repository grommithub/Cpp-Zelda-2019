#include "Enemy.h"

#include "Random.h"

std::vector<Pickup*>* Enemy::pickupVector{ nullptr };

Enemy::Enemy(Vector2 spawnPosition) : damage(1)
{


	tag = 'E';
	transform.position = spawnPosition;
	renderTransform.position = transform.position;
}

Enemy::~Enemy()
{
	DropLoot();
}

bool Enemy::Offscreen()
{
	if (renderTransform.position.x > WIDTH* SCALE || renderTransform.position.x < 0.0f || renderTransform.position.y < UI_HEIGHT * SCALE || renderTransform.position.y >(VIEWPORT_HEIGHT + UI_HEIGHT) * SCALE) return true;
	return false;
}

void Enemy::Die()
{
}

void Enemy::SetPickupVector(std::vector<Pickup*>* pickups)
{
	pickupVector = pickups;
}

void Enemy::DropLoot()
{
	if (Random::GetRandomInt() % 4 == 0)
	{
		pickupVector->push_back(new HeartPickup(middle - Vector2(2 * SCALE, 2 * SCALE)));
	}
}
