#include "theGame.h"
#include <future>
#include <iostream>
#include "Levers.h"
#include "startUI.h"
#include "someTools.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"
theGame::theGame()
	:isRunning(true), renderer(nullptr), window(nullptr), fileReader()
{

}

bool theGame::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER))
	{
		printf("fail to SDL_Init SDL_INIT_EVERYTHING : %s\n", SDL_GetError());
		return false;
	}
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
	{
		printf("fail to IMG_Init : %s\n", SDL_GetError());
		return false;
	}
	if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC))
	{
		printf("fail to MIX_Init : %s\n", SDL_GetError());
		return false;
	}
	if (TTF_Init())
	{
		printf("fail to TTF_Init : %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow(someTools::u8ToChar(u8"Test测试"), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	if (window == nullptr)
	{
		printf("fail to CreateWindow : %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("fail to CreateRenderer : %s\n", SDL_GetError());
		return false;
	}
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048))
	{
		printf("fail to Mix_OpenAudio : %s\n", SDL_GetError());
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF(R"(F:\code\work\TouhouMusicGame\resources\ttf\NotoSansSC-Regular.otf)", 32, nullptr, io.Fonts->GetGlyphRangesChineseFull());

	return true;
}

void theGame::Loop()
{
	loadingLever* loadLever = new loadingLever(renderer, window);
	levers toLever = Start;
	baseLever* lever = nullptr;
	auto newRoundLeverFunc = [&lever, this](std::string musicRoute, std::string backgroundImgRoute)
	{
		delete lever;
		lever = nullptr;
		lever = new roundLevel(renderer, window, fileReader, musicRoute, backgroundImgRoute);
	};
	while (isRunning)
	{
		std::future<void>asyncResult{};
		switch (toLever)
		{
		case Quit:
			isRunning = false;
			delete lever;
			goto end;
			break;
		case Start:
		{
			startUI ui(renderer);
			toLever = ui.run();
			continue;
		}
		case PristineBeat:
			asyncResult = std::async(std::launch::async, [&lever, this, &newRoundLeverFunc]() {
				fileReader.open(R"(F:\code\work\TouhouMusicGame\resources\musicNotationFile\PristineBeat.txt)", std::ios::in);
				newRoundLeverFunc(someTools::u8ToChar(u8R"(F:\code\work\TouhouMusicGame\resources\music\始原のビート ～ Pristine Beat.flac)"), {});
				});
			break;
		case ThirdEye:
			asyncResult = std::async(std::launch::async, [&lever, this, &newRoundLeverFunc]() {
				fileReader.open(R"(F:\code\work\TouhouMusicGame\resources\musicNotationFile\ZUN - Satori Maiden ~ 3rd eye (Dai) [suko's Normal].txt)", std::ios::in);
				newRoundLeverFunc(someTools::u8ToChar(u8R"(F:\code\work\TouhouMusicGame\resources\music\Satori Maiden ~ 3rd eye.mp3)"),
					someTools::u8ToChar(u8R"(F:\code\work\TouhouMusicGame\resources\img\satori(CUnet)(noise_scale)(Level2)(tta)(1280x720).png)"));
				});
			break;
		default:
			break;
		}
		while (asyncResult.wait_for(std::chrono::microseconds(8)) == std::future_status::timeout)//这里设为0的话有很大概率会开启的时候卡死，估计是0太快了（，然而似乎不设置也会，一定是异步问题
		{
			loadLever->resetLever();
			toLever = loadLever->running();
			if (toLever == Quit)
				goto end;//已知问题：由于异步，跳出的时候会等待asyncResult析构，所以会等其加载完之后才关闭
		}
		toLever = lever->running();
	}
end:
	delete loadLever;
	fileReader.close();
}

void theGame::Shutdown()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}