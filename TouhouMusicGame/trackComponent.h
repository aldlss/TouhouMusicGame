#pragma once
#include "baseComponent.h"
#include <queue>
#include "musicalNote.h"

class trackComponent :
	public baseComponent
{
protected:
	std::queue<musicalNote::NodeInfo>waitingTrack;
	std::queue<musicalNote*>playingTrack;
	SDL_Scancode lastCode;
	int pressed;
public:
	trackComponent(baseGameObject* ownerInput, std::queue<musicalNote::NodeInfo>&& waitingTrack, int priorityInput = 10);
	void update() override;
	void processInput(const Uint8* keyState) override;
};

