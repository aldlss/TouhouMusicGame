#include "timer.h"

Uint32 timer::musicStartTime = 0;
Uint32 timer::ticksCount = 0;
Uint32 timer::relativePassTime = 0;
double timer::deltaTime = 0.0;
double timer::noteFallsTime = 4;
double timer::FPS = 60;

void timer::ticks(double fps)
{
	FPS = fps;
	int fpsTime = 1000 / fps;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + fpsTime))
		SDL_Delay(1);
	deltaTime = SDL_GetTicks() - ticksCount;
	ticksCount = SDL_GetTicks();
	relativePassTime = ticksCount - musicStartTime;
}