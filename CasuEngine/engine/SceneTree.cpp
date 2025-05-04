#include "SceneTree.h"

void SceneTree::AddScene(Scene* scene)
{
	scene->SetRoot(this);
	currentScene = scene;
}

void SceneTree::Init()
{
	if (currentScene)
	{
		currentScene->Init();
	}
}

void SceneTree::Ready()
{
	if (currentScene)
	{
		currentScene->Ready();
	}
}


void SceneTree::Update(float deltaTime)
{
	if (currentScene)
	{
		currentScene->Update(deltaTime);
	}
}

void SceneTree::Render()
{
	if (currentScene)
	{
		currentScene->Render();
	}
}

void SceneTree::Destroy()
{
	if (currentScene)
	{
		currentScene->Destroy();
		delete currentScene;
	}
}
