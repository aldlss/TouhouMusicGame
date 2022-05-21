#pragma once
class gameState
{
public:
	static int combo;
	static struct BeatCount
	{
		int miss, bad, great, perfect;
	}beatCount;
	static void Initialize();
};