#include "AnimatorController.h"
#include <iostream>

AnimatorController::AnimatorController() : currentState(nullptr), interval(0.1f), timer(0.0f), currentSpriteIndex(0), loop(true), pingPong(false), done(false)
{
}

void AnimatorController::SetAnimationState(AnimationState* state)
{
	if (state == currentState) return;
	//set every value to the value of the state
	currentState = state;
	timer = 0;
	currentSpriteIndex = state->firstFrame;
	interval = state->animationInterval;
	loop = state->loop;
	pingPong = state->pingPong;
}

int AnimatorController::GetCurrentSpriteIndex()
{
	return currentSpriteIndex;
}

void AnimatorController::Animate(float dt)
{
	if (currentState == nullptr || currentState->firstFrame >= currentState->lastFrame) return;
	timer += dt;
	if (timer >= interval)
	{
		done = false;
		currentSpriteIndex++;
		timer -= interval;
	}
	if (currentSpriteIndex > currentState->lastFrame)
	{
		done = true;
		if(loop)
		currentSpriteIndex = currentState->firstFrame;
		else currentSpriteIndex = currentState->lastFrame;
	}
}

bool AnimatorController::GetAnimationComplete()
{
	return done;
}
