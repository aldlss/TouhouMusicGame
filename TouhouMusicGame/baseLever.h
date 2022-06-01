#pragma once
#include "baseGameObject.h"
#include "spriteComponent.h"
#include "theGame.h"
#include "textObject.h"
#include <vector>
class baseLever
{
protected:
	std::vector<spriteComponent*>allSprite;
	std::vector<baseGameObject*>allGameObject;
	std::vector<baseGameObject*>pendingObjects;
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::unordered_map<std::string, SDL_Texture*>Textures;
	std::unordered_map<std::string, TTF_Font*>Fonts;
	std::unordered_map<std::string, baseGameObject*>globalObject;
	theGame::levers toLever;
	bool isRunning;
	bool isUpdate;
	Mix_Music* music;
public:
	baseLever(SDL_Renderer* renderer, SDL_Window* window);
	~baseLever();
	void createGameObject(baseGameObject* willBeCreatedObject);
	bool deleteGameObject(baseGameObject* willBeDeletedObject);
	void addSprite(spriteComponent* willBeAddedComponent);
	bool removeSprite(spriteComponent* willBeRemovedComponent);

	void resetLever();//重新设置running为true，适用于不用重新加载或者还原局面的情况
	theGame::levers running();
	void event();
	void update();
	void render();
	virtual void globalEvent();//全局事件，发现不加这个可能有点难搞
	SDL_Texture* getTexture(const std::string& name);
	baseGameObject* getGlobalObject(const std::string& name);
};
