#pragma once
class Random
{
	static int index;
	static unsigned char rngTable[256];
public:
	static int GetRandomInt();
	static int GetRandomInt(int max);
	static int GetRandomInt(int min, int max);
	static void ResetRandom();
};

