#include "startUI.h"
#include "someTools.h"
#include "gameSetting.h"
startUI::startUI(SDL_Renderer* renderer)
	:renderer(renderer)
{

}


theGame::levers startUI::run()
{
	bool running = true;
	SDL_Event event;
	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	// int uiFlags = 1;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("touhou", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground);
			// ImGui::SetWindowSize({ 1280,720 });
			ImGui::SetWindowPos({ 0,0 });
			someTools::imguiTextCentered(someTools::u8ToChar(u8"车万音游"));
			ImGui::SetCursorPosY(150);
			if (someTools::imguiButtonCentered(someTools::u8ToChar(u8"开始游戏"), { 300,100 }))
			{
				return theGame::ThirdEye;
			}
			ImGui::NewLine();
			ImGui::SliderInt(someTools::u8ToChar(u8"音量"), &gameSetting::musicVolume, 0, 128);
			Mix_VolumeMusic(gameSetting::musicVolume);
			float noteSpeed = gameSetting::getNoteSpeed();
			ImGui::SliderFloat(someTools::u8ToChar(u8"音符下落速度"), &noteSpeed, 1, 11);
			gameSetting::setNoteSpeed(noteSpeed);
			ImGui::BeginGroup();
			someTools::imguiTextCentered(someTools::u8ToChar(u8"游戏玩法："));
			someTools::imguiTextCentered(someTools::u8ToChar(u8"黄圈与红圈重合时敲击空格，跟着音乐走，会好很多的~"));
			ImGui::EndGroup();

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

		}
		ImGui::Render();
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);
	}
	return theGame::Quit;
}
