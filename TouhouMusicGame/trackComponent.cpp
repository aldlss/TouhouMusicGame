#include "trackComponent.h"
#include "timer.h"
#include "gameSetting.h"
trackComponent::trackComponent(baseGameObject* ownerInput, std::queue<musicalNote::NodeInfo>&& waitingTrack, int priorityInput)
	:baseComponent(ownerInput, priorityInput), waitingTrack(waitingTrack), playingTrack(), pressed(0)
{

}

void trackComponent::update()
{

	while (!waitingTrack.empty())
	{
		auto& nodeInfo = waitingTrack.front();
		if (nodeInfo.beatTime - timer::noteFallsTime + timer::musicStartTime <= timer::relativePassTime)
		{
			auto node = musicalNote::createRoundNoteSimple(this->owner->getGame(), nodeInfo.beatTime, nodeInfo.endTime, nodeInfo.category);
			node->getComponent<noteComponent>()->belongTrack = &playingTrack;
			playingTrack.push(node);
			waitingTrack.pop();
		}
		else break;
	}
	while (!playingTrack.empty())
	{
		auto node = playingTrack.front();
		auto nodeCom = node->getComponent<noteComponent>();
		if (nodeCom->beatTime + timer::musicStartTime <= timer::relativePassTime)
			int a = 1;
		if (timer::relativePassTime > nodeCom->beatTime + gameSetting::missSlower)
		{
			node->setState(node->Dead);
			nodeCom->nowNoteState = nodeCom->Miss;
			playingTrack.pop();
		}
		else break;
	}
}

void trackComponent::processInput(const Uint8* keyState)
{
	if (playingTrack.empty())return;//空的就不用看了（
	auto node = playingTrack.front();
	auto nodeCom = node->getComponent<noteComponent>();
	if (!keyState[nodeCom->beatKey])
	{
		pressed = 0;
		return;
	}
	if (nodeCom->endTime == 0)//暂时只写黄键的
	{
		if (pressed)return;
		pressed = 1;
		int deltaTime = timer::relativePassTime - nodeCom->beatTime;
		if (deltaTime <= gameSetting::badFaster)return;//注意大于小于
		else
		{
			node->setState(node->Dead);
			playingTrack.pop();//偷懒（
			if (deltaTime < gameSetting::goodFaster)nodeCom->nowNoteState = nodeCom->Bad;//BAD~GOOD
			else if (deltaTime < gameSetting::perfectFaster)nodeCom->nowNoteState = nodeCom->Good;//GOOD~PERFECT
			else if (deltaTime <= gameSetting::perfectSlower)nodeCom->nowNoteState = nodeCom->Perfect;//PERFECT~PERFECT
			else if (deltaTime <= gameSetting::goodSlower)nodeCom->nowNoteState = nodeCom->Good;//PERFECT~GOOD
			else if (deltaTime <= gameSetting::badSlower)nodeCom->nowNoteState = nodeCom->Bad;//GOOD~BAD
			else nodeCom->nowNoteState = noteComponent::Miss;
		}
	}
}
