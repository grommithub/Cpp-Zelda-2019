#pragma once
#include "AnimationState.h"

class AnimatorController
{
	AnimationState* currentState;
	float interval;
	float timer;
	int currentSpriteIndex;
	bool loop;
	bool pingPong;
	bool done;

public:
	AnimatorController();
	void SetAnimationState(AnimationState* state);
	int GetCurrentSpriteIndex();
	void Animate(float dt);
	bool GetAnimationComplete();
};

