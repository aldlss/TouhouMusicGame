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
	std::unordered_map<std::string, textObject*>Texts;
	theGame::levers toLever;
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
	void event();
	void update();
	void render();
	SDL_Texture* getTexture(const std::string& name);
	textObject* getTextObject(const std::string& name);
};
