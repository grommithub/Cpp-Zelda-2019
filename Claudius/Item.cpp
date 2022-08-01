#include "Item.h"
#include "Inventory.h"
#include "Camera.h"

Player* Pickup::player{ nullptr };

Pickup::Pickup(Vector2 position) : tada(false), sprite(nullptr)
{
	transform.position = position;
	SpriteCutter::GetResourceManager()->LoadImageFromFile(spriteSheet, "../Assets/items-sheet.png");
	transform.SetUniformScale(SCALE);
	renderTransform = transform;
	

	debugColour = Color::Blue();

}

void Pickup::SetCollider()
{
	collider.SetSize(sprite->source.w * SCALE, sprite->source.h * SCALE);
	collider.SetPosition(transform.position.x, transform.position.y);
	debugRect = collider.rect;
}

Pickup::~Pickup()
{
	delete sprite;
}

void Pickup::SetPlayer(Player* p)
{
	player = p;
}

void Pickup::UseItem(Player* player)
{
	std::cout << "use" << std::endl;
}

void Pickup::Render(RenderManager& renderer, bool debug)
{
	renderTransform.position = transform.position - Camera::GetCamPosition();
	debugRect.x = (int)renderTransform.position.x;
	debugRect.y = (int)renderTransform.position.y;
	renderer.Render(*sprite, renderTransform);
	if (debug)
		renderer.Render(debugRect, debugColour);
}

Collider& Pickup::GetCollider()
{
	return collider;
}


