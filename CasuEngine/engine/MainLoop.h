#pragma once

#include "../core/Singleton.h"
#include "CasuEngineDef.h"
#include "SceneTree.h"

class MainLoop: public Singleton<MainLoop>
{
public:
	bool IsRunning();
	void Run();
	
	std::string GetTitle();
	int GetWidth();
	int GetHeight();

	void SetTitle(const std::string& title);
	void SetWidth(int width);
	void SetHeight(int height);

	void LoadConfig();
	void SaveConfig();
private:
	bool isRunning = false;
	std::string title;
	int width = 600;
	int height = 600;

	void Update(float deltaTime);
	void Render();
	void Exit();

};