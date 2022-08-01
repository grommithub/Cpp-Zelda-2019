#pragma once
#include "SpriteCutter.h"
#include "Collider.h"
#include "Camera.h"

class Projectile
{
	int damage;
	int speed;
	int direction;
	float maxDistance;
	
	Transform trans;
	Transform renderTransform;
	Image image;
	Sprite* sprite;
	Collider collider;
	bool enemy;

public:
	Projectile(Vector2 startPosition, int dir, int type);

	enum Types
	{
		Arrow,
		Rock
	};

	bool IsEnemy() { return enemy; }
	int GetDamage() { return damage; }
	Vector2 GetMiddle();
	void Update(float dt);
	void Render(RenderManager& renderer, bool debug);
};

