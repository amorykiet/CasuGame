#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

#define USE_EDITOR

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    rlImGuiSetup(true);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        rlImGuiBegin();
        ClearBackground(RAYWHITE);

		// Imgui demo
		ImGui::ShowDemoWindow();


        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
