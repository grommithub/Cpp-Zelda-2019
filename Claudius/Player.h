#pragma once
#include "Entity.h"
#include "KeyCode.h"
#include "Controls.h"
#include "Sword.h"

//sprite numbers

#define DOWN1  0
#define DOWN2  1
#define RIGHT1 2
#define RIGHT2 3
#define UP1	   4
#define UP2    5
#define DSTAB  6
#define RSTAB  7
#define USTAB  8
#define TADA   9

//animation numbers
//W: walk
//S: standing
//A: attack

#define WDOWN  0
#define WRIGHT 1
#define WUP    2

#define SDOWN  3
#define SRIGHT 4
#define SUP	   5

#define ADOWN  6
#define ARIGHT 7
#define AUP	   8

class Player : public Entity
{
	bool up;
	bool down;
	bool left;
	bool right;
	
	bool aButton;
	bool bButton;
		
	bool stabbing;
	bool moving;

	float stabTime;
	float currentStabTime;
	bool canStab;

	Sword* sword;

	void SetStabbing();
	void CreateAnimations();
	void SetAnimation();
	Vector2 middle;
	int maxHealth;

	Sound stabSound;

public:

	Player();
	~Player();
	void Update(float dt);
	void Render(RenderManager& renderer, bool debug);
	void GiveHealth(int health);
	void GiveResources(int type, int amount);

	int& GetTotalHealth() { return maxHealth; }
	Transform& GetTransform(){ return transform; }
	bool GetStabbing() { return stabbing; }
	Sword* GetSword();

	void OnKeyDown(KeyCode key);
	void OnKeyUp(KeyCode key);
	const Controls controls;
	void OnTilemapCollide(Rectangle tile);
};
