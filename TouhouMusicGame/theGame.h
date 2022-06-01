#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <unordered_map>
#include <string>
#include <fstream>
class theGame
{
public:
	//	初始化
	bool Initialize();
	//	主循环
	void Loop();
	//	游戏结束
	void Shutdown();
	//  构造函数
	theGame();
	enum levers { Quit, Continue, Start, PristineBeat, ThirdEye };
private:
	bool isRunning;
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::ifstream fileReader;
	// std::unordered_map<std::string, SDL_Texture* >Textures;
};