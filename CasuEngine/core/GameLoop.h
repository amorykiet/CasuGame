#pragma once

#include "CasuEngineDef.h"
#include "Singleton.h"
#include "EntityManager.h"
#include "tinyxml2.h"

// TODO: loop through components instead of entities
class GameLoop : public Singleton<GameLoop>
{
public:

	void Run()
	{

		Configuration(GAME_CONFIG_FILE);

		InitWindow(m_screenWidth, m_screenHeight, m_title.c_str());

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

	void Configuration(const std::string& fileName)
	{
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) == tinyxml2::XML_SUCCESS)
		{
			ReadConfig(doc);
		}
		else
		{
			WriteConfigFile(fileName, GAME_ENGINE_TITLE, 800, 450);
		}
	}

	void WriteConfigFile(const std::string& fileName, const std::string& title, int width, int height)
	{
		tinyxml2::XMLDocument doc;

		// Create root element  
		tinyxml2::XMLElement* root = doc.NewElement("game");
		doc.InsertFirstChild(root);

		// Create config element  
		tinyxml2::XMLElement* config = doc.NewElement("window");
		config->SetAttribute("title", title.c_str());
		config->SetAttribute("width", width);
		config->SetAttribute("height", height);
		root->InsertEndChild(config);

		// Save to file  
		if (doc.SaveFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
		{
			throw std::runtime_error("Failed to save XML file");
		}
	}

	void ReadConfig(tinyxml2::XMLDocument& doc)
	{
		tinyxml2::XMLElement* root = doc.RootElement();
		if (root != nullptr)
		{
			tinyxml2::XMLElement* config = root->FirstChildElement("window");
			if (config != nullptr)
			{
				const char* title = config->Attribute("title");
				int width, height;
				config->QueryIntAttribute("width", &width);
				config->QueryIntAttribute("height", &height);

				if (title != nullptr)
				{
					m_title = title;
				}

				if (width > 0 && height > 0)
				{
					m_screenWidth = width;
					m_screenHeight = height;
				}
			}
		}
	}

private:
	float deltaTime{ 0.0f };
	int m_screenWidth = 320;
	int m_screenHeight = 180;
	std::string m_title = GAME_ENGINE_TITLE;
};