#include "AnimationState.h"

AnimationState::AnimationState(int first, int last, float interval) : loop(true), pingPong(false)
{
	firstFrame = first;
	lastFrame = last;
	animationInterval = interval;
}

AnimationState::AnimationState(int first, int last, float interval, bool looping) : loop(looping), pingPong(false)
{
	firstFrame = first;
	lastFrame = last;
	animationInterval = interval;
	looping = looping;
}
