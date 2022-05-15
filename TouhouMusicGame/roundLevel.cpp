#include "roundLever.h"
#include "gameSetting.h"

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

	musicalNote::readMusicNotationFileSimple(file, waitingTracks);
	auto a = trackObject::createCrackObjectSimple(this, std::move(waitingTracks[0]));
	trackObjects.emplace_back(a);
	timer::musicStartTime = SDL_GetTicks();
}

void roundLevel::event()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			tolever = theGame::Quit;
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

