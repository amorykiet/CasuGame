#pragma once

#include "../core/Singleton.h"
#include "CasuEngineDef.h"
#include "SceneTree.h"

class MainLoop: public Singleton<MainLoop>
{
public:
	bool IsRunning() const { return isRunning; }
	void Run();

private:
	bool isRunning = false;

	void Update(float deltaTime);
	void Render();
	void Exit();
};