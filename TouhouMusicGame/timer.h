#pragma once
#include "SDL2/SDL.h"
class timer
{
public:
	static Uint32 ticksCount, musicStartTime, relativePassTime;
	static double deltaTime, noteFallsTime, FPS;
	static void ticks(double fps);
	// static double getStartTime(double beatTime) { return 0.35 + 3.65 * pow((12 - gameSetting::noteSpeed) / 11, 1.31); }
};