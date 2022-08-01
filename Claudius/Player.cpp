#include "Player.h"
#include "ScreenDimentions.h"
#include "SpriteCutter.h"
#include "Item.h"


Player::Player() : controls(Controls::PlayerOne()), up(false), down(false), left(false), right(false), stabbing(false), stabTime(0.5f), canStab(true), maxHealth(6)
{

	health = 6;
	tag = 'P';
	speed = 120.0f;
	direction = UP;
	knockBackSpeed = 350;

	transform.position = Vector2(WIDTH * SCALE, (HEIGHT + UI_HEIGHT) * SCALE) / 2;

	resource->LoadImageFromFile(sheet, "../Assets/link-sheet.png");
	CreateAnimations();
	sprites = SpriteCutter::GetSprites(10, sheet);
	animator->SetAnimationState(animations[WUP]);

	invincibilityTime = 0.5f;

	sword = new Sword(1);

	resource->LoadSoundFromFile(stabSound, "../Assets/Audio/LOZ_Sword_Slash.ogg");
}

Player::~Player()
{
	delete sword;
	for (AnimationState* animation : animations) delete animation;
}

Sword* Player::GetSword()
{
	if (sword != nullptr) return sword; 
	return nullptr; 
}

void Player::OnKeyDown(const KeyCode key)
{
	if (currentInvincibilityTime > 0) return;
	if (key == controls.leftKey)
	{
		left = true;
		direction = LEFT;
	}
	else if (key == controls.rightKey)
	{
		right = true;
		direction = RIGHT;
	}
	else if (key == controls.upKey)
	{
		up = true;
		direction = UP;
	}
	else if (key == controls.downKey)
	{
		down = true;
		direction = DOWN;
	}
	if (key == controls.swordKey)
	{
		aButton = true;
		SetStabbing();
	}
	if (key == controls.itemKey)
	{
		bButton = true;
	}
	if (key == KeyCode::E)
	{
		delete sword;
		sword = nullptr;
	}
	if (key == KeyCode::T) sword = new Sword(1);

}

void Player::OnKeyUp(KeyCode key)
{
	if (key == controls.leftKey) left = false;
	else if (key == controls.rightKey) right = false;
	else if (key == controls.upKey)	up = false;
	else if (key == controls.downKey) down = false;

	if (key == controls.swordKey)
	{
		aButton = false;
		canStab = true;
	}

	if (key == controls.itemKey) bButton = true;
}

void Player::Update(float dt)
{
	
	moving = (up || down || left || right);
	if (currentInvincibilityTime > invincibilityTime / 2)
	{
		moving = false;
	}
	if (sword != nullptr)
	{
		if (stabbing)
		{
			moving = false;
			float distance;
			if (currentStabTime <= stabTime / 1.15f) distance = 1.0f;
			else distance = 0.75f;
			sword->SetTransAndCollider(direction, transform.position, distance);
		}
		sword->SetHitBoxActive(stabbing && (currentStabTime >= stabTime / 2));
		stabbing = (currentStabTime > 0.0f);
	}

	currentStabTime -= dt;

	if (moving)
	{
		Move(dt);
	}
	Entity::Update(dt);
	SetAnimation();
	if (health > maxHealth) health = maxHealth;

}

void Player::SetStabbing()
{
	if (!canStab || stabbing || sword == nullptr) return;
	soundPlayer->PlaySound(stabSound, 0);
	stabbing = true;
	currentStabTime = stabTime;
	canStab = false;
}

void Player::CreateAnimations()
{
	for (int i = 0; i < 3; i++) //walking
	{
		AnimationState* walking = new AnimationState(i * 2, i * 2 + 1, 0.25f);
		animations.push_back(walking);
	}
	for (int i = 0; i < 3; i++) //standing
	{
		AnimationState* standing = new AnimationState(i * 2, i * 2, 0.0f);
		animations.push_back(standing);
	}
	for (int i = 0; i < 3; i++)
	{
		AnimationState* stabbing = new AnimationState(DSTAB + i, DSTAB + i, 0.0f, false);
		animations.push_back(stabbing);
	}
}

void Player::SetAnimation()
{
	if (stabbing && sword != nullptr)
	{
		switch (direction)
		{
		case LEFT:
			animator->SetAnimationState(animations[ARIGHT]);
			activeSprite.SetFlip(Sprite::Flip::Horizontal);
			break;
		case RIGHT:
			animator->SetAnimationState(animations[ARIGHT]);
			activeSprite.SetFlip(Sprite::Flip::None);
			break;
		case UP:
			animator->SetAnimationState(animations[AUP]);
			break;
		case DOWN:
			animator->SetAnimationState(animations[ADOWN]);
			break;
		default:
			break;
		}
	return; 
	}
	
	switch (direction)
	{

	case LEFT:
		{
		if (moving)
			animator->SetAnimationState(animations[WRIGHT]);
		else animator->SetAnimationState(animations[SRIGHT]);

			activeSprite.SetFlip(Sprite::Flip::Horizontal);
			direction = LEFT;
			break;
		}
	case RIGHT:
		{
		if (moving)
			animator->SetAnimationState(animations[WRIGHT]);
		else animator->SetAnimationState(animations[SRIGHT]);

			activeSprite.SetFlip(Sprite::Flip::None);
			direction = RIGHT;
			break;
		}
	case UP:
		{
		if (moving)
			animator->SetAnimationState(animations[WUP]);
		else animator->SetAnimationState(animations[SUP]);

			activeSprite.SetFlip(Sprite::Flip::None);
			direction = UP;
			break;
		}
	case DOWN:
		{
		if (moving)
			animator->SetAnimationState(animations[WDOWN]);
		else animator->SetAnimationState(animations[SDOWN]);

			activeSprite.SetFlip(Sprite::Flip::None);
			direction = DOWN;
			break;
		}

	default:
		break;
	}
}

void Player::Render(RenderManager& renderer, bool debug)
{
	if(stabbing && sword != nullptr) sword->Render(renderer, debug);
	Entity::Render(renderer, debug);
}

void Player::GiveHealth(int extraHealth)
{
	health += extraHealth;
	if (health > maxHealth) extraHealth = maxHealth;
}

void Player::GiveResources(int type, int amount)
{
	switch (type)
	{
	case Pickup::HEALTH:
		GiveHealth(amount);
		break;
	case Pickup::RUPEES:
		std::cout << "monies" << std::endl;
		break;
	case Pickup::BOMBS:
		std::cout << "bombs" << std::endl;
		break;
	case Pickup::KEYS:
		std::cout << "key" << std::endl;
		break;
	}
}

void Player::OnTilemapCollide(Rectangle tile)
{
	Entity::OnTilemapCollide(tile);
	moving = false;
}
