#include "MainLoop.h"
#include "SceneTree.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"

#include "vld.h"
#include "Editor.h"

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

//#define USE_EDITOR

int main(void)
{

#if defined(USE_EDITOR)

	Editor::GetInstance()->Run();

#else
    if (!SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE)) {
		printf("Failed to load scene from XML\n");
		printf("Please create a scene first\n");
		return -1;
    }
	//Run the main loop
	MainLoop::GetInstance()->Run();
#endif
return 0;
}