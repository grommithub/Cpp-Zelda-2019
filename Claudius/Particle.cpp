#include "Particle.h"
#include "ScreenDimentions.h"
#include <iostream>
#include "Camera.h"

Particle::Particle(int particleType, Vector2 position)
{
	controller = AnimatorController();
	trans.position = position - Camera::GetCamPosition();
	trans.SetUniformScale(SCALE);


		SpriteCutter::GetResourceManager()->LoadImageFromFile(sheet, "../Assets/death-effect.png");
		sprites = SpriteCutter::GetSprites(4, sheet);
		animation = new AnimationState(0, 3, 0.1f);

	controller.SetAnimationState(animation);
}

Particle::~Particle()
{
	for (Sprite* s : sprites)
	{
		delete s;
	}
	delete animation;

}

void Particle::Animate(float dt)
{
	controller.Animate(dt);
}

void Particle::Render(RenderManager& renderer)
{
	renderer.Render(*sprites[controller.GetCurrentSpriteIndex()], trans);
}
