#include "Octorok.h"
#include "Camera.h"

Octorok::Octorok(Vector2 position) : Enemy(position), randomnessCountdown(0.2f * Random::GetRandomInt(0, 5)), randomInterval(0.0f)
{
	direction = UP;
	damage = 1;
	health = 2;
	speed = 75.0f;
	SpriteCutter::GetResourceManager()->LoadImageFromFile(sheet, "../Assets/enemies.png");
	sprites = SpriteCutter::GetSprites(4, sheet);
	CreateAnimations();
}

Octorok::~Octorok()
{
	for (AnimationState* anim : animations) delete anim;
}

void Octorok::CreateAnimations()
{
	AnimationState* animation = new AnimationState(0, 1, 0.5f);
	animations.push_back(animation);
	AnimationState* hurt = new AnimationState(2, 3, 0.15f);
	animations.push_back(hurt);
}

void Octorok::SetAnimation()
{
	if (currentInvincibilityTime > 0) animator->SetAnimationState(animations[1]);
	else
		animator->SetAnimationState(animations[0]);

	activeSprite.SetFlip(Sprite::Flip::None);
	
	switch (direction)
	{
	case UP:
		renderTransform.SetRotation(0);
		activeSprite.SetFlip(Sprite::Flip::Vertical);
		break;
	case DOWN:
		renderTransform.SetRotation(0);
		break;
	case LEFT:
		renderTransform.SetRotation(90);
		break;
	case RIGHT:
		renderTransform.SetRotation(-90);
		break;
	default:
		break;
	}
}

void Octorok::Shoot()
{
	std::cout << "shoot" << std::endl;
}

void Octorok::OnTilemapCollide(Rectangle tile)
{
	Entity::OnTilemapCollide(tile);

	if (currentInvincibilityTime > 0.0f) return;
	if (direction == LEFT) direction = RIGHT;
	else if (direction == RIGHT) direction = LEFT;
	else if (direction == DOWN) direction = UP;
	else if (direction == UP) direction = DOWN;
}

void Octorok::Update(float dt)
{
	if(Offscreen())
	return;

	Entity::Update(dt);
	SetAnimation();

	if (currentInvincibilityTime > 0.0f)
	return;
	
	
	Move(dt);
	renderTransform.position = transform.position - Camera::GetCamPosition();
	
	if (Offscreen())
	{
		switch (direction)
		{
		case LEFT: direction = RIGHT; break;
		case RIGHT: direction = LEFT; break;
		case DOWN:  direction = UP; break;
		case UP: direction = DOWN; break;
		}
	Move(dt);
	}

	randomnessCountdown -= dt;
	if (randomnessCountdown <= 0)
	{
		if (direction == 4) Shoot();

		int i;
		if (direction == UP || direction == DOWN) i = 0;
		else i = 2;
		direction = Random::GetRandomInt(0, 1) + i;
		randomnessCountdown = 0.1f * Random::GetRandomInt(20, 30);
	}
}
