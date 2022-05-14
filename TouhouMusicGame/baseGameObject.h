#ifndef _BASE_GAME_OBJECT_
#define _BASE_GAME_OBJECT_
#include "baseComponent.h"
#include "overallGame.h"
#include <vector>
class baseComponent;
class baseGameObject
{
private:
	std::vector<baseComponent*>ownComponent;
	overallGame* nowGame;
public:
	overallGame* getGame()const { return nowGame; }
	baseGameObject(overallGame* nowGame);
	~baseGameObject();
	void update();
	void addComponent(baseComponent* willBeAddedComponent);
	bool removeComponent(baseComponent* willBeRemovedComponent);
};

#endif //_BASE_GAME_OBJECT_