#include "gameState.h"

int gameState::combo = 0;
gameState::BeatCount gameState::beatCount{ 0,0,0,0 };

void gameState::Initialize()
{
	combo = 0;
	beatCount = { 0,0,0,0 };
}
