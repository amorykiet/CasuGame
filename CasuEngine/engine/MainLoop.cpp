#include "MainLoop.h"
#include "raylib.h"

void MainLoop::Run()
{
	InitWindow(320, 180, "Game made by Casu Engine");

	SetTargetFPS(60);

	//Init nodes from top to bottom, parrent to child
	SceneTree::GetInstance()->Init();

	//Get the nodes ready from bottom to top, child to parent
	SceneTree::GetInstance()->Ready();

	while (!WindowShouldClose())
	{
		Update(GetFrameTime());

		BeginDrawing();

		ClearBackground(RAYWHITE);
		Render();

		EndDrawing();
	}

	Exit();

	CloseWindow();
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
