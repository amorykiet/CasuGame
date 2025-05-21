#include "MainLoop.h"
#include "SceneTree.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"

#include "vld.h"

//#define USE_EDITOR

#if defined(USE_EDITOR)
#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "Editor.h"
#endif


int main(void)
{

#if defined(USE_EDITOR)

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "CasuEngine Editor");
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    rlImGuiSetup(true);
    Editor::GetInstance()->Init();
    while (!WindowShouldClose())
    {
        if (!ImGui::GetIO().WantCaptureMouse) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f / camera.zoom);
                camera.target = Vector2Add(camera.target, delta);
            }
            float wheel = GetMouseWheelMove();
            if (wheel != 0)
            {
                Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                camera.offset = GetMousePosition();
                camera.target = mouseWorldPos;
                float scale = 0.2f * wheel;
                camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);
            }
        }

        BeginDrawing();
        rlImGuiBegin();
        ClearBackground(RAYWHITE);

        Editor::GetInstance()->Update();
        
        BeginMode2D(camera);
        Editor::GetInstance()->Render();
		EndMode2D();

        rlImGuiEnd();
        EndDrawing();
    }

    Editor::GetInstance()->Close();
    rlImGuiShutdown();
    CloseWindow();

#else
    if (!SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE)) {
	    Scene* scene = new Scene();
	    scene->SetName("MainScene");
	    World* world = new World();
	    Player* player = new Player();
	    world->AddChild(player);
	    scene->AddChild(world);
	    SceneTree::GetInstance()->AddScene(scene);
    }
	//Run the main loop
	MainLoop::GetInstance()->Run();
#endif
return 0;
}