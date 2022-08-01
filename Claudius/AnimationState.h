#pragma once
class AnimationState
{
public:
	AnimationState(int first, int last, float interval);
	AnimationState(int first, int last, float interval, bool looping);
	int firstFrame;
	int lastFrame;
	float animationInterval;
	bool loop;
	bool pingPong;
};

