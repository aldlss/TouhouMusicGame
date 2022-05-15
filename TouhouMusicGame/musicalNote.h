#pragma once
#include <SDL2/SDL.h>
#include "baseGameObject.h"
#include "spriteComponent.h"
#include "noteComponent.h"
#include "transformChangeComponent.h"
#include "transformComponent.h"
#include "fstream"
#include <string>
#include <queue>
class musicalNote :
	public baseGameObject
{
protected:

	spriteComponent* sprite;
	noteComponent* note;
	transformChangeComponent* transformChange;
	transformComponent* transform;
	Uint32 startTime;
public:
	musicalNote(baseLever* nowLever, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, noteComponent::category ownCategory, double x = 0, double y = 0, double z = 0,
		SDL_Texture* texture = nullptr, int drawOrder = 100);
	struct NodeInfo
	{
		int track;
		noteComponent::category category;
		Uint32 [[deprecated("No use")]] startTime;
		Uint32 beatTime, endTime;
	};
	static void readMusicNotationFileSimple(std::ifstream& file, std::vector<std::queue<NodeInfo>>& tracks);
	static musicalNote* createRoundNoteSimple(baseLever* nowLever, const Uint32& beatTime, const Uint32& endTime, const noteComponent::category& ownCategory);
};