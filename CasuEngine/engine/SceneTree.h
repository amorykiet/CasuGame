#pragma once
#include "../core/Singleton.h"
#include "Node.h"
#include <vector>
#include <string>

class SceneTree : public Singleton<SceneTree>
{
public:

	void AddScene(Scene* scene);
	void Init();
	void Ready();
	void Update(float deltaTime);
	void Render();
	void Destroy();

private:
	Scene* currentScene;
};