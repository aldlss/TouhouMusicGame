#include <iostream>

#include "roundLever.h"
#include "gameSetting.h"
#include "gameState.h"
#include "someTools.h"
#include "imgObject.h"

roundLevel::roundLevel(SDL_Renderer* renderer, SDL_Window* window, std::ifstream& file, std::string musicRoute, std::string backgroundImgRoute, std::mutex& rendererMutex)
	:baseLever(renderer, window), musicNotationFile(file)
{
	/*std::string test{};
	bool ok = musicNotationFile.is_open();
	std::getline(musicNotationFile, test);
	你妈的，先偷一行走了，怪不得我说怎么读不到
	*/

	SDL_Texture* texture = nullptr;
	{
		std::lock_guard<std::mutex>lock(rendererMutex);
		texture = IMG_LoadTexture(renderer, R"(resources\img\round.png)");
	}
	if (texture != nullptr)Textures.emplace("Round", texture);
	else printf("READ IMG ERROR : %s\n", SDL_GetError());
	{
		std::lock_guard<std::mutex>lock(rendererMutex);
		texture = IMG_LoadTexture(renderer, R"(resources\img\roundTrack.png)");
	}
	if (texture != nullptr)Textures.emplace("roundTrack", texture);
	else printf("READ IMG ERROR : %s\n", SDL_GetError());
	texture = nullptr;
	{
		std::lock_guard<std::mutex>lock(rendererMutex);
		texture = IMG_LoadTexture(renderer, backgroundImgRoute.c_str());
	}
	if (texture != nullptr)
	{
		Textures.emplace("background", texture);
		auto backgroundImg = new imgObject(this);
		backgroundImg->getComponent<spriteComponent>()->setTexture(texture);
		backgroundImg->getComponent<transformComponent>()->setPosition(gameSetting::width >> 1, gameSetting::height >> 1, 0);
		globalObject.emplace("backgroundImg", backgroundImg);
	}
	else printf("READ IMG ERROR : %s\n", SDL_GetError());
	gameSetting::standardY = gameSetting::height / 3;
	gameSetting::standardX = gameSetting::width / 2;
	gameSetting::setOriginalTargetScale(3, 3, 0.5, 0.5);
	gameState::Initialize();

	TTF_Font* font = TTF_OpenFont(R"(resources\ttf\MerriweatherSans-VariableFont_wght.ttf)", 64);
	Fonts.emplace("MerriweatherSans", font);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);

	auto text = new textObject(this, font, nullptr, gameSetting::width >> 1, (gameSetting::height >> 2) * 3, 0, 120);
	globalObject.emplace("judgeText", text);
	text = new textObject(this, font, nullptr, (gameSetting::width >> 2) * 3, gameSetting::height / 3, 0, 120);
	globalObject.emplace("comboText", text);
	music = Mix_LoadMUS(musicRoute.c_str());
	Mix_VolumeMusic(gameSetting::musicVolume);

	musicalNote::readMusicNotationFileSimple(file, waitingTracks);
	auto a = trackObject::createCrackObjectSimple(this, std::move(waitingTracks[0]));
	trackObjects.emplace_back(a);
	// SDL_Delay(10000);
	timer::musicStartTime = SDL_GetTicks();
	Mix_PlayMusic(music, 0);
}