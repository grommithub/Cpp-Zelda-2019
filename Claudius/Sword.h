#pragma once

#include "SpriteCutter.h"
#include "Collider.h"
#include "Transform.h"
#include "RenderManager.h"

class Sword
{
	enum directions
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	Image image;
	Sprite* sprite;
	int damage;
	Collider collider;
	bool active;
	Transform transform;
	Transform renderTransform;

	Vector2 offset;
	
	int width;
	int height;

	Rectangle debugRect;
	Color debugColor;

public:
	Sword(int lvl);
	~Sword();
	void Render(RenderManager& renderer, bool debug);

	Collider& GetCollider() { return collider; }

	int GetDamage() { return damage; }

	void SetHitBoxActive(bool state);
	Sprite* GetSwordSprite() { return sprite; }
	void SetTransAndCollider(int direction, Vector2 position, float distanceMultiplier);
	
};
