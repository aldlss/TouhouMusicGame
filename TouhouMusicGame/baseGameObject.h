#ifndef _BASE_GAME_OBJECT_
#define _BASE_GAME_OBJECT_
#include "baseComponent.h"
#include <vector>
#include "SDL2/SDL.h"
class baseComponent;
class baseGameObject
{
public:
	enum State { Alive, Dead };

	baseGameObject(class baseLever* nowLever);//加了class竟然就没有环形依赖了，玄学了
	~baseGameObject();
	void processInput(const Uint8* keyState);
	void update();
	void addComponent(baseComponent* willBeAddedComponent);
	bool removeComponent(baseComponent* willBeRemovedComponent);
	State getState()const { return nowState; }
	void setState(State state) { nowState = state; }
	baseLever* getGame()const { return nowLever; }

	template <typename T>T* getComponent()
	{
		for (auto component : ownComponent)
		{
			T* temp = dynamic_cast<T*>(component);
			if (temp != nullptr)
				return temp;
		}
		return nullptr;
	}//模板按正常写在cpp会报无法解析错误
protected:
	std::vector<baseComponent*>ownComponent;
	baseLever* nowLever;
	State nowState;
};

#endif //_BASE_GAME_OBJECT_