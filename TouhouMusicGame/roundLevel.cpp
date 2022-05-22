#include "roundLever.h"
#include "gameSetting.h"
#include "gameState.h"

roundLevel::roundLevel(SDL_Renderer* renderer, SDL_Window* window, std::ifstream& file)
	:baseLever(renderer, window), musicNotationFile(file)
{
	/*std::string test{};
	bool ok = musicNotationFile.is_open();
	std::getline(musicNotationFile, test);
	你妈的，先偷一行走了，怪不得我说怎么读不到
	*/

	auto texture = IMG_LoadTexture(renderer, R"(F:\code\work\TouhouMusicGame\resources\img\round.png)");
	if (texture != nullptr)Textures.emplace("Round", texture);
	else printf("READ IMG ERROR : %s\n", SDL_GetError());
	texture = IMG_LoadTexture(renderer, R"(F:\code\work\TouhouMusicGame\resources\img\roundTrack.png)");
	if (texture != nullptr)Textures.emplace("roundTrack", texture);
	else printf("READ IMG ERROR : %s\n", SDL_GetError());
	gameSetting::standardY = gameSetting::height / 3;
	gameSetting::standardX = gameSetting::width / 2;
	gameSetting::setNoteSpeed(10);
	gameSetting::setOriginalTargetScale(3, 3, 0.5, 0.5);
	gameState::Initialize();
	TTF_Font* font = TTF_OpenFont(R"(F:\code\work\TouhouMusicGame\resources\ttf\MerriweatherSans-VariableFont_wght.ttf)", 64);
	Fonts.emplace("MerriweatherSans", font);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	auto text = new textObject(this, font, nullptr, gameSetting::width >> 1, (gameSetting::height >> 2) * 3, 0, 120);
	globalObject.emplace("judgeText", text);
	text = new textObject(this, font, nullptr, (gameSetting::width >> 2) * 3, gameSetting::height / 3, 0, 120);
	globalObject.emplace("comboText", text);


	musicalNote::readMusicNotationFileSimple(file, waitingTracks);
	auto a = trackObject::createCrackObjectSimple(this, std::move(waitingTracks[0]));
	trackObjects.emplace_back(a);
	timer::musicStartTime = SDL_GetTicks();
}
