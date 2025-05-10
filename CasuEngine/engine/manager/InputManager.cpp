#include "InputManager.h"
#include "../core/Keyboard.h"
#include "../core/Mouse.h"

bool InputManager::IsKeyPressed(int key)
{
	return RKeyboard::IsKeyPressed(key);
}

bool InputManager::IsKeyDown(int key)
{
	return RKeyboard::IsKeyDown(key);
}

bool InputManager::IsKeyReleased(int key)
{
	return RKeyboard::IsKeyReleased(key);
}

bool InputManager::IsKeyUp(int key)
{
	return RKeyboard::IsKeyUp(key);
}

bool InputManager::IsMouseButtonPressed(int button)
{
	return RMouse::IsButtonPressed(button);
}

bool InputManager::IsMouseButtonDown(int button)
{
	return RMouse::IsButtonDown(button);
}

bool InputManager::IsMouseButtonReleased(int button)
{
	return RMouse::IsButtonReleased(button);
}

bool InputManager::IsMouseButtonUp(int button)
{
	return RMouse::IsButtonUp(button);
}

int InputManager::GetMouseX()
{
	return RMouse::GetX();
}

int InputManager::GetMouseY()
{
	return RMouse::GetY();
}

int InputManager::GetMouseWheelMove()
{
	return RMouse::GetWheelMove();
}

Vector2 InputManager::GetMousePosition()
{
	return RMouse::GetPosition();
}

void InputManager::SetMousePosition(int x, int y)
{
	RMouse::SetPosition(x, y);
}
