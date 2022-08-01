#include "Sword.h"
#include "RenderManager.h"
#include "ScreenDimentions.h"
#include "Camera.h"

Sword::Sword(int lvl) : damage(1), active(false), width(8), height(16), debugColor(Color::Blue())
{
	
	sprite = new Sprite();
	transform.SetUniformScale(SCALE);
	switch (lvl)
	{
	case 1:
		SpriteCutter::GetResourceManager()->LoadImageFromFile(image, "../Assets/items-sheet.png");
		sprite->SetImage(image);
		damage = 1;
		sprite->SetSource(0, 0, 7, 16);
		break;
	default:
		SpriteCutter::GetResourceManager()->LoadImageFromFile(image, "../Assets/items-sheet.png");
		sprite->SetImage(image);
		break;
	}
	renderTransform = transform;
}

Sword::~Sword()
{
	delete sprite;
}

void Sword::Render(RenderManager& renderer, bool debug)
{
	renderTransform.position = transform.position - Camera::GetCamPosition();
	renderTransform.rotation = transform.rotation;
	renderer.Render(*sprite, renderTransform);

	debugRect.x = collider.rect.x - (int)Camera::GetCamPosition().x;
	debugRect.y = collider.rect.y - (int)Camera::GetCamPosition().y;

	if (debug)
	{
		renderer.Render(debugRect, debugColor);
	}
}

void Sword::SetTransAndCollider(int direction, Vector2 position, float distanceMultiplier)
{

	//I'm hardcoding because I never need to change this
	Vector2 middle = position + Vector2(8.0f, 8.0f);
	switch (direction)
	{
	case LEFT:
		transform.SetRotation(90);
		sprite->SetFlip(Sprite::Flip::Vertical);
		transform.SetPosition(middle.x - (11.0f * SCALE * distanceMultiplier), middle.y - 1.0f * SCALE);
		offset = Vector2(-4.0f, 3.0f);
		collider.SetSize(height * SCALE, width * SCALE);
		break;

	case RIGHT:
		transform.SetRotation(90);
		sprite->SetFlip(Sprite::Flip::None);
		transform.SetPosition(middle.x + (15.0f * SCALE * distanceMultiplier), middle.y - 1.0f * SCALE);
		offset = Vector2(-4.0f, 3.0f);
		collider.SetSize(height * SCALE, width * SCALE);
		break;

	case UP:
		transform.SetRotation(0);
		sprite->SetFlip(Sprite::Flip::None);
		transform.SetPosition(position.x + 11.0f, position.y - (13.0f * SCALE * distanceMultiplier));
		collider.SetSize(width * SCALE, height * SCALE);
		offset = Vector2::Zero();
		break;

	case DOWN:
		transform.SetRotation(0); 
		sprite->SetFlip(Sprite::Flip::Vertical);
		transform.SetPosition(position.x + 11.0f, position.y + (13.0f * SCALE * distanceMultiplier));
		collider.SetSize(width * SCALE, height * SCALE);
		offset = Vector2::Zero();
		break;

	default:
		break;
	}
	collider.SetPosition((int)transform.position.x + (int)(offset.x * SCALE), (int)transform.position.y + (int)(offset.y * SCALE));

	debugRect.w = collider.rect.w;
	debugRect.h = collider.rect.h;
}

void Sword::SetHitBoxActive(bool state)
{
	active = state;
}
