#pragma once
#include "baseComponent.h"
#include "SDL2/SDL.h"
#include "queue"
class noteComponent :
	public baseComponent
{
public:
	int track;
	SDL_Scancode beatKey;//敲击的键
	Uint32 beatTime;//敲击时的时间（相对于歌曲）
	Uint32 endTime;//结束的时间（如果为连续音符）,0位短键
	enum category { GREEN, YELLOW, BLUE };//参考弹幕神乐黄绿蓝键（
	category ownCategory;
	std::queue<class musicalNote*>* belongTrack;
	enum nodeState { Active, Miss, Bad, Good, Perfect };
	nodeState nowNoteState;
	noteComponent(baseGameObject* ownerInput, int track, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, category ownCategory, int priorityInput = 40);
	~noteComponent() override;
};//音符组件