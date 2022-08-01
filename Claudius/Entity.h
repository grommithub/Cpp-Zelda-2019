#pragma once
#include "Sprite.h"
#include "Image.h"
#include "Collider.h"
#include "Transform.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "AnimationState.h"
#include "AnimatorController.h"
#include "Particle.h"
#include <iostream>

#include "SoundManager.h"
#include "Sound.h"
#include "Music.h"

#include "ScreenDimentions.h"
#include "SpriteCutter.h"



class Entity
{
public:
	Entity();
	~Entity();
	virtual void Update(float dt);
	virtual void Render(RenderManager& renderer, bool debug);

	bool TakeDamage(int incomingDamage);
	bool TakeDamage(int incomingDamage, Vector2 source);
	virtual void OnTilemapCollide(Rectangle tile);
	Collider& GetCollider() { return collider; }
	static void SetResourceManager(ResourceManager& r);
	int GetHealth() { return health; }
	int& GetHealthRef() { return health; }
	virtual void Die();
	Vector2 GetMiddle() { return middle; }
	static void SetParticleVector(std::vector<Particle*>& vector) { particleVector = &vector; }
	static void SetSoundPlayer(SoundManager* s) { soundPlayer = s; }

protected:
	static ResourceManager* resource;
	static SoundManager* soundPlayer;
	static std::vector<Particle*>* particleVector;
	
	Vector2 middle;
	std::vector<AnimationState*> animations;
	AnimatorController* animator;
	Rectangle debugRect;
	Transform renderTransform;
	int health;
	float speed;
	int direction;
	int activeSpriteIndex;
	enum directions
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	Transform transform;
	Collider collider;
	Sprite activeSprite;
	Image sheet;
	std::vector<Sprite*> sprites;
	virtual void CreateAnimations() = 0;
	virtual void SetAnimation() = 0;
	char tag;

	float invincibilityTime;
	float currentInvincibilityTime;

	void Knockback(float dt);
	Vector2 knockBackDirection;
	float knockBackSpeed;

	/*
		P: player
		E: enemy
		T: terrain
		W: water
		N: nothing
	*/

	virtual void Move(float dt);

	Color debugColor;
};