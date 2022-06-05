#include "loadingLever.h"
#include "imgObject.h"
#include "gameSetting.h"
#include "someTools.h"
#include "textObject.h"
loadingLever::loadingLever(SDL_Renderer* renderer, SDL_Window* window)
	:baseLever(renderer, window), count(0)
{
	TTF_Font* font = TTF_OpenFont(R"(resources\ttf\MaShanZheng-Regular.ttf)", 64);
	// TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	Fonts.emplace("MaShanZheng", font);

	auto loadImg = IMG_LoadTexture(renderer, R"(resources\img\loading.png)");
	Textures.emplace("loadImg", loadImg);
	auto loading = new imgObject(this);
	loading->getComponent<spriteComponent>()->setTexture(loadImg);
	loading->getComponent<transformComponent>()->setPosition(gameSetting::width >> 1, gameSetting::height >> 1, 0);
	loading->getComponent<transformComponent>()->setScale(0.2, 0.2, 1);
	loading->getComponent<transformChangeComponent>()->setRotationVelocityX(0.35);
	globalObject.emplace("loading", loading);

	auto loadText = new textObject(this, font, nullptr, gameSetting::width >> 1, gameSetting::height / 3 * 2, 0, 50);
	loadText->getComponent<fontComponent>()->serColor({ 224,137,24,255 });//我想的是枫叶般的颜色，但我觉得很明显不像（
	loadText->getComponent<fontComponent>()->setString(someTools::u8ToChar(u8"少女祈祷中"));
	globalObject.emplace("loadText", loadText);
}

void loadingLever::globalEvent()
{
	auto text = globalObject.find("loadText");
	switch (++count)
	{
	case 5:
		text->second->getComponent<fontComponent>()->setString(someTools::u8ToChar(u8"少女祈祷中."));
		break;
	case 10:
		text->second->getComponent<fontComponent>()->setString(someTools::u8ToChar(u8"少女祈祷中.."));
		break;
	case 15:
		text->second->getComponent<fontComponent>()->setString(someTools::u8ToChar(u8"少女祈祷中..."));
		break;
	case 20:
		text->second->getComponent<fontComponent>()->setString(someTools::u8ToChar(u8"少女祈祷中...."));
		break;
	case 25:
		text->second->getComponent<fontComponent>()->setString(someTools::u8ToChar(u8"少女祈祷中"));
		count = 0;
		break;
	default:
		break;
	}
	isRunning = false;
}
