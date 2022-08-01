#include "Projectile.h"

Projectile::Projectile(Vector2 startPosition, int dir, int type)
{
	trans.position = startPosition;
	direction = dir;
	switch (type)
	{
	case Rock:
		//image = 
		break;
	default:
		break;
	}
}

Vector2 Projectile::GetMiddle()
{
	Vector2 mid = trans.position;
	mid.x += collider.rect.w / 2;
	mid.y += collider.rect.h / 2;
	return mid;
}

void Projectile::Update(float dt)
{
}

void Projectile::Render(RenderManager& renderer, bool debug)
{
	renderTransform.position = trans.position - Camera::GetCamPosition();
	renderer.Render(*sprite, renderTransform);
	//if(debug)
		//renderer.Render(collider.rect, )
}
