#pragma once

#include "../core/Singleton.h"
#include "CasuEngineDef.h"
#include "../core/Vector2.h"

class InputManager : public Singleton<InputManager> 
{
public:
	static bool IsKeyPressed(int key);
	static bool IsKeyDown(int key);
	static bool IsKeyReleased(int key);
	static bool IsKeyUp(int key);

	static bool IsMouseButtonPressed(int button);
	static bool IsMouseButtonDown(int button);
	static bool IsMouseButtonReleased(int button);
	static bool IsMouseButtonUp(int button);
	static int GetMouseX();
	static int GetMouseY();
	static int GetMouseWheelMove();
	static Vector2 GetMousePosition();
	static void SetMousePosition(int x, int y);

};