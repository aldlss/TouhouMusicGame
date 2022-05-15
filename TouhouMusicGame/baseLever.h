#pragma once
#include "baseGameObject.h"
#include "spriteComponent.h"
#include "theGame.h"
#include <vector>
class baseLever
{
protected:
	std::vector<spriteComponent*>allSprite;
	std::vector<baseGameObject*>allGameObject;
	std::vector<baseGameObject*>pendingObjects;
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unordered_map<std::string, SDL_Texture* >Textures;
	theGame::levers tolever;
	bool isRunning;
	bool isUpdate;
public:
	baseLever(SDL_Renderer* renderer, SDL_Window* window);
	~baseLever();
	void createGameObject(baseGameObject* willBeCreatedObject);
	bool deleteGameObject(baseGameObject* willBeDeletedObject);
	void addSprite(spriteComponent* willBeAddedComponent);
	bool removeSprite(spriteComponent* willBeRemovedComponent);

	theGame::levers running();
	virtual void event();//默认是全部处理，但我认为有些是不用处理的，索性继承了
	void update();
	void render();
	SDL_Texture* getTexture(const std::string& name);
};
