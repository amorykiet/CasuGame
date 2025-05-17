#include "MainLoop.h"
#include "manager/AudioManager.h"
#include "manager/RenderManager.h"

void MainLoop::Run()
{
	RenderManager::GetInstance()->Init("Casu Engine", 800, 500);

	//Init audio device
	AudioManager::GetInstance()->Init();

	//Init nodes from top to bottom, parrent to child
	SceneTree::GetInstance()->Init();

	//Get the nodes ready from bottom to top, child to parent
	SceneTree::GetInstance()->Ready();

	isRunning = true;

	while (!WindowShouldClose())
	{
		AudioManager::GetInstance()->Update();

		Update(GetFrameTime());

		RenderManager::GetInstance()->BeginDrawing();
		RenderManager::GetInstance()->ClearBackground(RAYWHITE);
		
		RenderManager::GetInstance()->BeginShaderMode();
		Render();
		RenderManager::GetInstance()->EndShaderMode();

		RenderManager::GetInstance()->EndDrawing();
	}

	isRunning = false;

	Exit();

	AudioManager::GetInstance()->Close();

	RenderManager::GetInstance()->Close();
}

void MainLoop::Update(float deltaTime)
{
	SceneTree::GetInstance()->Update(deltaTime);
}

void MainLoop::Render()
{
	SceneTree::GetInstance()->Render();
}

void MainLoop::Exit()
{
	SceneTree::GetInstance()->Destroy();
}
