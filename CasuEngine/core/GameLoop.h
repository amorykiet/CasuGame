#pragma once

#include "Singleton.h"
#include "EntityManager.h"


// TODO: loop through components instead of entities
class GameLoop : public Singleton<GameLoop>
{
public:

	void Run()
	{
		// Initialization
		//--------------------------------------------------------------------------------------
		// TODO: Should be set in configuration
		const int screenWidth = 800;
		const int screenHeight = 450;

		InitWindow(screenWidth, screenHeight, "Casu engine");

		SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
		//--------------------------------------------------------------------------------------

		Init();
		while (!WindowShouldClose())
		{
			Update();

			BeginDrawing();

			ClearBackground(RAYWHITE);
			Render();

			EndDrawing();
		}

		Exit();

		CloseWindow();        // Close window and OpenGL context
	}

	void Init()
	{
		EntityManager::GetInstance()->Init();
	}

	void Update()
	{
		EntityManager::GetInstance()->Update(GetFrameTime());
	}

	void Render()
	{
		EntityManager::GetInstance()->Render();
	}
	

	void Exit()
	{
		EntityManager::GetInstance()->Destroy();
	}

private:
	float deltaTime{ 0.0f };
};