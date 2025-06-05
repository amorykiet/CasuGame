#pragma once
#include "../core/Singleton.h"
#include "Node.h"
#include <vector>
#include <string>

class SceneTree : public Singleton<SceneTree>
{
public:

	void AddScene(Scene* scene);
	Scene* GetCurrentScene();
	void Init();
	void Ready();
	void Update(float deltaTime);
	void Render();
	void Destroy();

	void SaveCurrentSceneToXML(const std::string& filePath);
	void SaveCurrentSceneToXML();
	bool LoadSceneFromXML(const std::string& filePath);

	Node* LoadNodeFromScene(const std::string& filePath);

private:
	Scene* currentScene;
	std::string currentSceneFilePath;
};