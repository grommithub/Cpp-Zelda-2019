#include "Entity.h"
#include "ScreenDimentions.h"
#include "Camera.h"


ResourceManager* Entity::resource{ nullptr };
std::vector<Particle*>* Entity::particleVector{ nullptr };
SoundManager* Entity::soundPlayer{ nullptr };

Entity::Entity() : health(1), tag('N'), direction(DOWN), speed(1.0f), debugColor(Color::Blue()), activeSpriteIndex(0), animator(new AnimatorController()), invincibilityTime(0.25f), currentInvincibilityTime(0.0f), knockBackSpeed(350.0f)
{
	transform.SetUniformScale(SCALE);
	resource->LoadImageFromFile(sheet, "../Assets/missing_image.png");
	activeSprite.SetImage(sheet);
	activeSprite.SetSource(0, 0, activeSprite.image->width, activeSprite.image->height);
	collider.rect.w = activeSprite.image->width * SCALE;
	collider.rect.h = activeSprite.image->height * SCALE;
	collider.SetPosition((int)transform.position.x, (int)transform.position.y);
	debugRect = collider.rect;
	renderTransform = transform;
}

Entity::~Entity()
{
	for (Sprite* sp : sprites) delete sp;

	particleVector->push_back(new Particle(0, transform.position));
	delete animator;
}

bool Entity::TakeDamage(int incomingDamage)
{
	if (currentInvincibilityTime <= 0)
	{
		health -= incomingDamage;
		currentInvincibilityTime = invincibilityTime;
		return true;
	}
	return false;
}

bool Entity::TakeDamage(int incomingDamage, Vector2 source)
{
	if (!TakeDamage(incomingDamage)) return false;

	Vector2 thisMid = transform.position;
	thisMid.x += (float)collider.rect.w / 2;
	thisMid.y += (float)collider.rect.h / 2;

	Vector2 difference = thisMid - source;

	if(difference.x * difference.x > difference.y * difference.y)
	{
		//sideways
		if (difference.x >= 0)
		{
			knockBackDirection = Vector2::Right() * knockBackSpeed;
			direction = RIGHT;
		}
		else
		{
			knockBackDirection = Vector2::Left() * knockBackSpeed;
			direction = LEFT;
		}
	}
	else
	{
		if (difference.y >= 0)
		{
			knockBackDirection = Vector2::Down() * knockBackSpeed;
			direction = DOWN;
		}
		else
		{
			knockBackDirection = Vector2::Up() * knockBackSpeed;
			direction = UP;
		}
	}
	return true;
}



void Entity::OnTilemapCollide(Rectangle tile)
{
	switch (direction)
	{
	case UP:
		transform.position.y = static_cast<float>(tile.y + tile.h + 1);
		break;

	case DOWN:
		transform.position.y = static_cast<float>(tile.y - collider.rect.h - 1);
		break;

	case LEFT:
		transform.position.x = static_cast<float>(tile.x + tile.w + 1);
		break;

	case RIGHT:
		transform.position.x = static_cast<float>(tile.x - collider.rect.w - 1);
		break;
	default:
		break;
	}
}

void Entity::Die()
{
	
}

void Entity::Knockback(float dt)
{
	transform.position += knockBackDirection * dt;
}

void Entity::Move(float dt)
{
	Vector2 moveDir = Vector2();
	switch (direction)
	{
	case LEFT:
		moveDir = Vector2::Left();
		break;
	case RIGHT:
		moveDir = Vector2::Right();
		break;
	case DOWN:
		moveDir = Vector2::Down();
		break;
	case UP:
		moveDir = Vector2::Up();
		break;
	case 4:
		moveDir = Vector2::Zero();
	default:
		//std::cout << "Invalid direction" << std::endl;
		break;
	}
	transform.position += moveDir * speed * dt;
}

void Entity::Render(RenderManager& renderer, bool debug)
{
	renderTransform.position = transform.position - Camera::GetCamPosition();

	debugRect.x = static_cast<int>(renderTransform.position.x);
	debugRect.y = static_cast<int>(renderTransform.position.y);

	activeSprite.source = sprites[activeSpriteIndex]->source;
	renderer.Render(activeSprite, renderTransform);
	if (debug)
	{
		renderer.Render(debugRect, debugColor);
	}
}

void Entity::SetResourceManager(ResourceManager& r)
{
	resource = &r;
}

void Entity::Update(float dt)
{



	animator->Animate(dt);
	activeSpriteIndex = animator->GetCurrentSpriteIndex();
	activeSprite = *sprites[activeSpriteIndex];
	collider.SetPosition((int)transform.position.x, (int)transform.position.y);
	middle = transform.position + Vector2((float)collider.rect.w / 2, (float)collider.rect.h / 2);
	
	currentInvincibilityTime -= dt;
	if (currentInvincibilityTime > invincibilityTime / 2)
	{
		Knockback(dt);
	}
	else if (currentInvincibilityTime < 0.0f)
	{
		currentInvincibilityTime = 0.0f;
	}
}
