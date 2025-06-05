#include "MainLoop.h"
#include "manager/AudioManager.h"
#include "manager/RenderManager.h"
#include "manager/CollisionManager.h"
#include "tinyxml2.h"

bool MainLoop::IsRunning()
{
	return isRunning;
}

void MainLoop::Run()
{
	LoadConfig();

	RenderManager::GetInstance()->Init(title.c_str(), width, height);

	//Init audio device
	AudioManager::GetInstance()->Init();

	//Init nodes from top to bottom, parrent to child
	SceneTree::GetInstance()->Init();

	//Get the nodes ready from bottom to top, child to parent
	SceneTree::GetInstance()->Ready();

	isRunning = true;

	while (!WindowShouldClose())
	{
		AudioManager::GetInstance()->Update();

		Update(GetFrameTime());

		CollisionManager::GetInstance()->Update();

		RenderManager::GetInstance()->BeginDrawing();
		RenderManager::GetInstance()->ClearBackground(RAYWHITE);
		
		RenderManager::GetInstance()->BeginShaderMode();
		Render();
		RenderManager::GetInstance()->EndShaderMode();

		RenderManager::GetInstance()->EndDrawing();
	}

	isRunning = false;

	Exit();
	
	CollisionManager::GetInstance()->Close();

	AudioManager::GetInstance()->Close();

	RenderManager::GetInstance()->Close();

	SaveConfig();
}

std::string MainLoop::GetTitle()
{
	return title;
}

int MainLoop::GetWidth()
{
	return width;
}

int MainLoop::GetHeight()
{
	return height;
}

void MainLoop::SetTitle(const std::string& title)
{
	this->title = title;
}

void MainLoop::SetWidth(int width)
{
	this->width = width;
}

void MainLoop::SetHeight(int height)
{
	this->height = height;
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

void MainLoop::LoadConfig()
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(GAME_CONFIG_FILE) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLElement* root = doc.RootElement();
		if (root)
		{
			const char* titleAttr = root->Attribute("title");
			if (titleAttr)
			{
				title = titleAttr;
			}
			root->QueryIntAttribute("width", &width);
			root->QueryIntAttribute("height", &height);
		}
	}
}

void MainLoop::SaveConfig()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root = doc.NewElement("GameConfig");
	doc.InsertFirstChild(root);
	root->SetAttribute("title", title.c_str());
	root->SetAttribute("width", width);
	root->SetAttribute("height", height);
	doc.SaveFile(GAME_CONFIG_FILE);
}
