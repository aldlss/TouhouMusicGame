#pragma once
#include "SDL2/SDL.h"
#include "vector"
#include "string"
#include "imgui/imgui.h"
class someTools
{
public:
	//以给予的坐标为中心画图
	static int RenderCopyExByCenter(SDL_Renderer* renderer,
		SDL_Texture* texture,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);
	static std::vector<int>	readNumFromStr(std::string& str);
	static const char* u8ToChar(const char8_t* p);
	static void imguiTextCentered(std::string text);//创建在imgui中居中的文本
	static bool imguiButtonCentered(std::string label, const ImVec2& size);
};

