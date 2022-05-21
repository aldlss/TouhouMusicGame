#pragma once
#include "SDL2/SDL.h"
#include "timer.h"
#include "string"
class gameSetting
{
private:
	static double noteSpeed;
	static double originalScaleX, originalScaleY, targetScaleX, targetScaleY;

	static double decreaseScaleSpeedX, decreaseScaleSpeedY;
public:
	static void setNoteSpeed(double noteSpeedInput)
	{
		noteSpeed = noteSpeedInput;
		timer::noteFallsTime = (0.35 + 3.65 * pow((12 - noteSpeed) / 11, 1.31)) * 1000;//*1000因为是以毫秒计时
	}
	static void setOriginalTargetScale(double oX, double oY, double tX, double tY)
	{
		originalScaleX = oX;
		originalScaleY = oY;
		targetScaleX = tX;
		targetScaleY = tY;
		double delta = targetScaleX - originalScaleX;
		decreaseScaleSpeedX = delta / timer::noteFallsTime;
		delta = targetScaleY - originalScaleY;
		decreaseScaleSpeedY = delta / timer::noteFallsTime;
	}
	static int width, height;
	static int standardX, standardY;//指关卡比较所常用的坐标，一般是判定区之类的
	static double getDecreaseScaleSpeedX() { return decreaseScaleSpeedX; }
	static double getDecreaseScaleSpeedY() { return decreaseScaleSpeedY; }
	static double getOriginalScaleX() { return originalScaleX; }
	static double getOriginalScaleY() { return originalScaleY; }
	//指相对正中击打的时间是快了还是慢了
	static int badSlower, badFaster, goodSlower, goodFaster, perfectSlower, perfectFaster;
	// static int missSlower;这个好像不是很需要

	static SDL_Color missColor;
	static SDL_Color badColor;
	static SDL_Color greatColor;
	static SDL_Color perfectColor;
	static SDL_Color comboColor;

	static std::string missStr;
	static std::string badStr;
	static std::string greatStr;
	static std::string perfectStr;
	static std::string comboStr;
};