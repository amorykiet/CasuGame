#pragma once
#include "../core/Singleton.h"
#include "../core/Color.h"
#include "../core/Vector2.h"
#include "../core/Shader.h"
#include "../core/Texture.h"
#include "../core/Window.h"
#include "../core/Rectangle.h"

class RenderManager : public Singleton<RenderManager>
{
public:
	void Init();
	void Init(const char* title, int width, int height);
	void Close();
	void SetTargetFPS(int fps);
	void ClearBackground(const RColor& color);
	void ClearBackground();
	void BeginDrawing();
	void EndDrawing();
	void SetShader(std::string file);
	void SetDefaultShader();
	void BeginShaderMode();
	void EndShaderMode();


	// Drawing Circles
	void DrawCircleV(RVector2 center, float radius, const RColor& color);
	void DrawCircle(float centerX, float centerY, float radius, const RColor& color);
	void DrawCircleLinesV(RVector2 center, float radius, const RColor& color);
	void DrawCircleLines(float centerX, float centerY, float radius, const RColor& color);

	// Drawing Rectangles
	void DrawRectangleV(RVector2 position, RVector2 size, const RColor& color);
	void DrawRectangle(float posX, float posY, float width, float height, const RColor& color);
	void DrawRectangleLinesV(RVector2 position, RVector2 size, const RColor& color);
	void DrawRectangleLines(float posX, float posY, float width, float height, const RColor& color);
	
	// Drawing Lines
	void DrawLineV(RVector2 startPos, RVector2 endPos, const RColor& color);
	void DrawLine(float startPosX, float startPosY, float endPosX, float endPosY, const RColor& color);

	// Drawing Texture
	void DrawTexture(RTexture2D texture, RVector2 position, RColor tfloat = RAYWHITE);
	void DrawTexture(RTexture2D texture, float posX, float posY, RColor tint = RAYWHITE);
	void DrawTexture(RTexture2D texture, RVector2 position, float rotation, float scale, RColor tint = RAYWHITE);
	void DrawTexture(RTexture2D texture, float posX, float posY, float rotation, float scale, RColor tint = RAYWHITE);
	void DrawTextureRec(RTexture2D texture, RRectangle source, RVector2 position, RColor tint = RAYWHITE);
	void DrawTexturePro(RTexture2D texture, RRectangle source, RRectangle dest, RVector2 origin = RVector2(0, 0), float rotation = 0, RColor tint = RAYWHITE);

	void DrawTexture(std::string file, RVector2 position, RColor tint = RAYWHITE);
	void DrawTexture(std::string file, float posX, float posY, RColor tint = RAYWHITE);
	void DrawTexture(std::string file, RVector2 position, float rotation, float scale, RColor tint = RAYWHITE);
	void DrawTexture(std::string file, float posX, float posY, float rotation, float scale, RColor tint = RAYWHITE);
	void DrawTextureRec(std::string file, RRectangle source, RVector2 position, RColor tint = RAYWHITE);
	void DrawTexturePro(std::string file, RRectangle source, RRectangle dest, RVector2 origin = RVector2(0, 0), float rotation = 0, RColor tint = RAYWHITE);

	// Drawing Text
	void DrawText(const char* text, float posX, float posY, float fontSize, const RColor& color);
	void DrawText(const char* text, RVector2 position, float fontSize, const RColor& color);

private:
	RWindow* m_window;
	RShader* m_currentShader;
};