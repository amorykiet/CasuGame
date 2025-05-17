#include "RenderManager.h"
#include "ResourceManager.h"
#include "../core/Window.h"
#include "../core/RaylibException.h"

void RenderManager::Init()
{
	if (::IsWindowReady())
	{
		throw RRaylibException("Window already initialized");
	}
	m_window = new RWindow();
	m_window->Init(320, 180, "Game made by Casu Engine");
	m_window->SetTargetFPS(60);
	m_window->ClearBackground(RAYWHITE);
}

void RenderManager::Init(const char* title, int width, int height)
{
	if (::IsWindowReady())
	{
		throw RRaylibException("Window already initialized");
	}
	m_window = new RWindow();
	m_window->Init(width, height, title);
	m_window->SetTargetFPS(60);
	m_window->ClearBackground(RAYWHITE);
}

void RenderManager::Close()
{
	if (::IsWindowReady())
	{
		m_window->Close();
		delete m_window;
	}
	else
	{
		throw RRaylibException("Window not initialized");
	}
}

void RenderManager::SetTargetFPS(int fps)
{
	m_window->SetTargetFPS(fps);
}
void RenderManager::ClearBackground(const RColor& color)
{
	m_window->ClearBackground(color);
}
void RenderManager::ClearBackground()
{
	m_window->ClearBackground(RAYWHITE);
}
void RenderManager::BeginDrawing()
{
	m_window->BeginDrawing();
}
void RenderManager::EndDrawing()
{
	m_window->EndDrawing();
}

void RenderManager::SetShader(std::string file)
{
	RShader* shader = ResourceManager::GetInstance()->GetResource<RShader>(file);
	if (shader)
	{
		m_currentShader = shader;
	}
	else
	{
		throw RRaylibException("Shader not initialized");
	}
}

void RenderManager::SetDefaultShader()
{
	if (m_currentShader)
	{
		m_currentShader = nullptr;
	}
}

void RenderManager::BeginShaderMode()
{
	if (m_currentShader)
	{
		m_currentShader->BeginMode();
	}
	else
	{
		// If no shader is set, use the default shader
		::EndShaderMode();
	}
}

void RenderManager::EndShaderMode()
{
	if (m_currentShader)
	{
		m_currentShader->EndMode();
	}
}

void RenderManager::DrawCircleV(RVector2 center, float radius, const RColor& color)
{
	::DrawCircleV(center, radius, color);
}

void RenderManager::DrawCircle(float centerX, float centerY, float radius, const RColor& color)
{
	::DrawCircle(centerX, centerY, radius, color);
}

void RenderManager::DrawCircleLinesV(RVector2 center, float radius, const RColor& color)
{
	::DrawCircleLinesV(center, radius, color);
}

void RenderManager::DrawCircleLines(float centerX, float centerY, float radius, const RColor& color)
{
	::DrawCircleLines(centerX, centerY, radius, color);
}

void RenderManager::DrawRectangleV(RVector2 position, RVector2 size, const RColor& color)
{
	::DrawRectangleV(position, size, color);
}

void RenderManager::DrawRectangle(float posX, float posY, float width, float height, const RColor& color)
{
	::DrawRectangle(posX, posY, width, height, color);
}

void RenderManager::DrawRectangleLinesV(RVector2 position, RVector2 size, const RColor& color)
{
	::DrawRectangleLines(position.x, position.y, size.x, size.y, color);
}

void RenderManager::DrawRectangleLines(float posX, float posY, float width, float height, const RColor& color)
{
	::DrawRectangleLines(posX, posY, width, height, color);
}

void RenderManager::DrawLineV(RVector2 startPos, RVector2 endPos, const RColor& color)
{
	::DrawLineV(startPos, endPos, color);
}

void RenderManager::DrawLine(float startPosX, float startPosY, float endPosX, float endPosY, const RColor& color)
{
	::DrawLine(startPosX, startPosY, endPosX, endPosY, color);
}

void RenderManager::DrawTexture(RTexture2D texture, RVector2 position, RColor tint)
{
	texture.Draw(position, tint);
}

void RenderManager::DrawTexture(RTexture2D texture, float posX, float posY, RColor tint)
{
	texture.Draw(posX, posY, tint);
}

void RenderManager::DrawTexture(RTexture2D texture, RVector2 position, float rotation, float scale, RColor tint)
{
	texture.Draw(position, rotation, scale, tint);
}

void RenderManager::DrawTexture(RTexture2D texture, float posX, float posY, float rotation, float scale, RColor tint)
{
	RVector2 pos = {posX, posY};
	texture.Draw(pos, rotation, scale, tint);
}

void RenderManager::DrawTextureRec(RTexture2D texture, RRectangle source, RVector2 position, RColor tint)
{
	texture.Draw(source, position, tint);
}

void RenderManager::DrawTexture(std::string file, RVector2 position, RColor tint)
{
	RTexture* texture = ResourceManager::GetInstance()->GetResource<RTexture>(file);
	if (texture) {
		texture->Draw(position, tint);
	}
}

void RenderManager::DrawTexture(std::string file, float posX, float posY, RColor tint)
{
	RTexture* texture = ResourceManager::GetInstance()->GetResource<RTexture>(file);
	if (texture) {
		texture->Draw(posX, posY, tint);
	}
}

void RenderManager::DrawTexture(std::string file, RVector2 position, float rotation, float scale, RColor tint)
{
	RTexture* texture = ResourceManager::GetInstance()->GetResource<RTexture>(file);
	if (texture) {
		texture->Draw(position, rotation, scale, tint);
	}
}

void RenderManager::DrawTexture(std::string file, float posX, float posY, float rotation, float scale, RColor tint)
{
	RTexture* texture = ResourceManager::GetInstance()->GetResource<RTexture>(file);
	if (texture) {
		RVector2 pos = { posX, posY };
		texture->Draw(pos, rotation, scale, tint);
	}
}

void RenderManager::DrawTextureRec(std::string file, RRectangle source, RVector2 position, RColor tint)
{
	RTexture* texture = ResourceManager::GetInstance()->GetResource<RTexture>(file);
	if (texture) {
		texture->Draw(source, position, tint);
	}
}

void RenderManager::DrawText(const char* text, float posX, float posY, float fontSize, const RColor& color)
{
	::DrawText(text, posX, posY, fontSize, color);
}

void RenderManager::DrawText(const char* text, RVector2 position, float fontSize, const RColor& color)
{
	::DrawText(text, position.x, position.y, fontSize, color);
}