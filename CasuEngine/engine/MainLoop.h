#pragma once

#include "../core/Singleton.h"
#include "CasuEngineDef.h"
#include "SceneTree.h"

class MainLoop: public Singleton<MainLoop>
{
public:
	bool IsRunning() const { return isRunning; }
	void Run();
	
	std::string GetTitle() const { return title; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void SetTitle(const std::string& title) { this->title = title; }
	void SetWidth(int width) { this->width = width; }
	void SetHeight(int height) { this->height = height; }

private:
	bool isRunning = false;
	std::string title;
	int width = 600;
	int height = 600;

	void Update(float deltaTime);
	void Render();
	void Exit();
	void LoadConfig();
	void SaveConfig();

};