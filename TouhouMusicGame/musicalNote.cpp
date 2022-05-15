#include "musicalNote.h"

#include "baseLever.h"
#include "someTools.h"
#include "gameSetting.h"
#include "timer.h"

musicalNote::musicalNote(baseLever* nowLever, SDL_Scancode beatKey, Uint32 beatTime, Uint32 endTime, noteComponent::category ownCategory,
	double x, double y, double z, SDL_Texture* texture, int drawOrder)
	:baseGameObject(nowLever), startTime(0)
{
	transform = new transformComponent(this, x, y, z);
	// transformChange = new transformChangeComponent(this, vX, vY, vZ, aX, aY, aZ);
	transformChange = new transformChangeComponent(this);
	note = new noteComponent(this, 0, beatKey, beatTime, endTime, ownCategory);
	sprite = new spriteComponent(this, texture, drawOrder);
}

void musicalNote::readMusicNotationFileSimple(std::ifstream& file, std::vector<std::queue<NodeInfo>>& tracks)
{
	std::string eachLine;
	while (!std::getline(file, eachLine).eof())
	{
		auto temp = someTools::readNumFromStr(eachLine);
		double startTime = temp[2] + timer::musicStartTime - timer::noteFallsTime;//废弃占位，懒得改（
		if (!temp.empty())tracks[temp[0]].emplace(temp[0], static_cast<noteComponent::category>(temp[1]), startTime, temp[2], temp.size() == 4 ? temp[3] : 0);
	}
}

musicalNote* musicalNote::createRoundNoteSimple(baseLever* nowLever, const Uint32& beatTime, const Uint32& endTime, const noteComponent::category& ownCategory)
{
	auto texture = nowLever->getTexture("Round");
	auto temp = new musicalNote(nowLever, SDL_SCANCODE_SPACE, beatTime, endTime, ownCategory, gameSetting::standardX, gameSetting::standardY, 0, texture);
	temp->getComponent<transformChangeComponent>()->setScaleVelocity(gameSetting::getDecreaseScaleSpeedX(), gameSetting::getDecreaseScaleSpeedY(), 0);
	temp->getComponent<transformComponent>()->setScale(gameSetting::getOriginalScaleX(), gameSetting::getOriginalScaleY(), 1);
	return temp;
}


