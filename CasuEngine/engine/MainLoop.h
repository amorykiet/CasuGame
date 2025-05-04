#pragma once

#include "../core/Singleton.h"
#include "CasuEngineDef.h"
#include "SceneTree.h"

class MainLoop: public Singleton<MainLoop>
{
public:
	void Run();

private:
	void Update(float deltaTime);
	void Render();
	void Exit();
};