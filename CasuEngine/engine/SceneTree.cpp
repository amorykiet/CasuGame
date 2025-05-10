#include "SceneTree.h"
#include <tinyxml2.h> //XML handling

void SceneTree::AddScene(Scene* scene)
{
	scene->SetRoot(this);
	currentScene = scene;
}

void SceneTree::Init()
{
	if (currentScene)
	{
		currentScene->Init();
	}
}

void SceneTree::Ready()
{
	if (currentScene)
	{
		currentScene->Ready();
	}
}


void SceneTree::Update(float deltaTime)
{
	if (currentScene)
	{
		currentScene->Update(deltaTime);
	}
}

void SceneTree::Render()
{
	if (currentScene)
	{
		currentScene->Render();
	}
}

void SceneTree::Destroy()
{
	if (currentScene)
	{
		currentScene->Destroy();
		delete currentScene;
	}
}


void SceneTree::SaveCurrentSceneToXML(const std::string& filePath)
{
    if (!currentScene)
    {
        return;
    }

    tinyxml2::XMLDocument doc;

    // Create root element
    tinyxml2::XMLElement* root = doc.NewElement("Scene");
    doc.InsertFirstChild(root);

    currentScene->SerializeToXML(root, &doc);

    // Save to file
    tinyxml2::XMLError result = doc.SaveFile(filePath.c_str());
    if (result != tinyxml2::XML_SUCCESS)
    {
		printf("Error saving XML file: %s\n", doc.ErrorName());
    }
}

bool SceneTree::LoadSceneFromXML(const std::string& filePath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS)
	{
		printf("Error loading XML file: %s\n", doc.ErrorName());
		return false;
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("Scene");
	if (root)
	{
		if (!currentScene)
		{
			currentScene = new Scene();
		}
		else
		{
			currentScene->Destroy();
			delete currentScene;
			currentScene = new Scene();
		}
		currentScene->DeserializeFromXML(root);
	}
	else
	{
		printf("Error: No root element found in XML file.\n");
		return false;
	}

	return true;
}
