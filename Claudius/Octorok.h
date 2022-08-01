#pragma once
#include "Enemy.h"
#include "Random.h"
class Octorok :
	public Enemy
{
	void CreateAnimations();
	void SetAnimation();
	void Shoot();

	float randomnessCountdown;
	float randomInterval;

public:
	Octorok(Vector2 position);
	~Octorok();
	void OnTilemapCollide(Rectangle tile);
	void Update(float dt);
};

