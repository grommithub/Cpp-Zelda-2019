#pragma once

#include "Player.h"
#include "Image.h"
#include "Sprite.h"

#include "Rendermanager.h"

class Pickup
{
protected:
	static Player* player;
	bool tada;
	Transform transform;
	Transform renderTransform;
	Collider collider;
	Rectangle debugRect;
	Color debugColour;
	Image spriteSheet;
	Sprite* sprite;
	void SetCollider();
public:
	enum resourceType
	{
		HEALTH,
		TOTAL_HEALTH,
		RUPEES,
		BOMBS,
		KEYS
	};
	
	Pickup(Vector2 position);
	~Pickup();
	static void SetPlayer(Player* p);
	virtual void UseItem(Player* player);
	virtual Pickup* GivePlayerPickup() = 0;
	void Render(RenderManager& renderer, bool debug);
	Collider& GetCollider();
};



