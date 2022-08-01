#pragma once
#include "Image.h"
#include "Sprite.h"
#include "SpriteCutter.h"
#include "AnimatorController.h"
#include "RenderManager.h"
#include "Transform.h"


class Particle
{

	Image sheet;
	std::vector<Sprite*> sprites;
	AnimatorController controller;
	AnimationState* animation;
	Transform trans;
	enum Type
	{
		DEATH,
		POOF
	};
public:

	Particle(int particleType, Vector2 position);
	~Particle();
	void Animate(float dt);
	void Render(RenderManager& renderer);

	bool GetDone() { return controller.GetAnimationComplete(); }
};
