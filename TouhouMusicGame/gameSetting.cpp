#include "gameSetting.h"

double gameSetting::noteSpeed = 10;
int gameSetting::width = 1280;
int gameSetting::height = 720;
int gameSetting::standardX = width / 2;
int gameSetting::standardY = height / 2;

// int gameSetting::missSlower = 4000;
int gameSetting::badSlower = 125;
int gameSetting::goodSlower = 90;
int gameSetting::perfectSlower = 50;
int gameSetting::perfectFaster = -50;
int gameSetting::goodFaster = -90;
int gameSetting::badFaster = -125;

double gameSetting::originalScaleX = 1.0;
double gameSetting::originalScaleY = 1.0;
double gameSetting::targetScaleY = 3.0;
double gameSetting::targetScaleX = 3.0;
double gameSetting::decreaseScaleSpeedX = 1;
double gameSetting::decreaseScaleSpeedY = 1;

SDL_Color gameSetting::missColor{ 162,190,180,240 };
SDL_Color gameSetting::badColor{ 143,22,22,240 };
SDL_Color gameSetting::greatColor{ 240,200,50,240 };
SDL_Color gameSetting::perfectColor{ 255,255,0,240 };
SDL_Color gameSetting::comboColor{ 244,234,25,240 };


std::string gameSetting::missStr{ "MISS" };
std::string gameSetting::badStr{ "BAD" };
std::string gameSetting::greatStr{ "GREAT!" };
std::string gameSetting::perfectStr{ "PERFECT!!" };
std::string gameSetting::comboStr{ "Combo" };