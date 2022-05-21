#include "baseLever.h"
#include "gameSetting.h"
#include "timer.h"

baseLever::baseLever(SDL_Renderer* renderer, SDL_Window* window)
	:allSprite(), allGameObject(), renderer(renderer), window(window), Textures(), toLever(theGame::Quit), isRunning(true), pendingObjects(), isUpdate(false)
{

}

baseLever::~baseLever()
{
	while (!allGameObject.empty())
		delete allGameObject.back();
	for (auto& texture : Textures)
		SDL_DestroyTexture(texture.second);
	Textures.clear();
}


void baseLever::addSprite(spriteComponent* willBeAddedComponent)
{
	auto pos = allSprite.begin();
	int thisDrawOrder = willBeAddedComponent->getDrawOrder();
	while (pos != allSprite.end() && (*pos)->getDrawOrder() < thisDrawOrder)
		++pos;
	allSprite.insert(pos, willBeAddedComponent);
}

bool baseLever::removeSprite(spriteComponent* willBeRemovedComponent)
{
	for (auto pos = allSprite.begin(); pos != allSprite.end(); ++pos)
		if (willBeRemovedComponent == *pos)
		{
			allSprite.erase(pos);
			return true;
		}
	return false;
}

void baseLever::createGameObject(baseGameObject* willBeCreatedObject)
{
	if (isUpdate)
		pendingObjects.emplace_back(willBeCreatedObject);
	else
		allGameObject.emplace_back(willBeCreatedObject);
}

bool baseLever::deleteGameObject(baseGameObject* willBeDeletedObject)
{
	auto pos = pendingObjects.begin();
	if (pos != pendingObjects.end())
	{
		std::iter_swap(pos, pendingObjects.end() - 1);
		pendingObjects.pop_back();
	}

	pos = std::ranges::find(allGameObject, willBeDeletedObject);
	if (pos != allGameObject.end())
	{
		std::iter_swap(pos, allGameObject.end() - 1);
		allGameObject.pop_back();
	}
	return true;
}

void baseLever::event()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			toLever = theGame::Quit;
			break;
		default:
			break;
		}
	}
	auto keyState = SDL_GetKeyboardState(nullptr);
	for (auto gameObject : allGameObject)
		if (gameObject->getState() == gameObject->Alive)
			gameObject->processInput(keyState);

}

void baseLever::render()
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
	SDL_RenderClear(renderer);
	for (auto sprite : allSprite)
		sprite->draw(renderer);
	SDL_RenderPresent(renderer);
}

SDL_Texture* baseLever::getTexture(const std::string& name)
{
	const auto pos = Textures.find(name);
	if (pos == Textures.end())return nullptr;
	return pos->second;
}

textObject* baseLever::getTextObject(const std::string& name)
{
	const auto pos = Texts.find(name);
	if (pos == Texts.end())return nullptr;
	return pos->second;
}


void baseLever::update()
{
	timer::ticks(60);
	isUpdate = true;
	for (auto object : allGameObject)
		if (object->getState() == object->Alive)
			object->update();
	isUpdate = false;

	for (auto pendingObject : pendingObjects)
		allGameObject.emplace_back(pendingObject);
	pendingObjects.clear();

	std::vector<baseGameObject*> deadObjects;
	for (auto deadObject : allGameObject)
		if (deadObject->getState() == deadObject->Dead)
			deadObjects.emplace_back(deadObject);
	while (!deadObjects.empty())
	{
		delete deadObjects.back();
		deadObjects.pop_back();//事实证明，是要自己手动删的
	}
	// printf("fps:%lf\n", 1000 / timer::deltaTime);
}


theGame::levers baseLever::running()
{
	while (isRunning)
	{
		event();
		update();
		render();
	}
	return toLever;
}
