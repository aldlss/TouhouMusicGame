#pragma once
#include "baseComponent.h"
#include "SDL2/SDL.h"
class noteComponent :
	public baseComponent
{
public:
	SDL_Scancode beatKey;//敲击的键
	Uint32 beatTime;//敲击时的时间（相对于歌曲）
	Uint32 endTime;//结束的时间（如果为连续音符），默认0为短键
	noteComponent(baseGameObject* ownerInput, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, int priorityInput = 40);
};//音符组件

