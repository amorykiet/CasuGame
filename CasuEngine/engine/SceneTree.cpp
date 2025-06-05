#include "SceneTree.h"
#include <tinyxml2.h> //XML handling

void SceneTree::AddScene(Scene* scene)
{
	scene->SetRoot(this);
	currentScene = scene;
}

Scene* SceneTree::GetCurrentScene()
{
	return currentScene;
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

void SceneTree::SaveCurrentSceneToXML()
{
	if (currentSceneFilePath.empty())
	{
		printf("Error: No file path specified for saving the scene.\n");
		return;
	}
	SaveCurrentSceneToXML(currentSceneFilePath);
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
	if (!root)
	{
		printf("Error: No root element found in XML file.\n");
		return false;
	}
	currentSceneFilePath = filePath;
	const char* tagName = root->Attribute("type");
	currentScene = NodeFactory::Create(tagName);
	if (currentScene)
	{
		currentScene->DeserializeFromXML(root);
		currentScene->SetRoot(this);
		return true;
	}
	else
	{
		printf("Error creating scene from XML.\n");
		return false;
	}
}

Node* SceneTree::LoadNodeFromScene(const std::string& filePath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS)
	{
		printf("Error loading XML file: %s\n", doc.ErrorName());
		return nullptr;
	}
	tinyxml2::XMLElement* root = doc.FirstChildElement("Scene");
	if (root)
	{
		const char* tagName = root->Attribute("type");
		Node* node = NodeFactory::Create(tagName);
		node->DeserializeFromXML(root);
		return node;
	}
	else
	{
		printf("Error: No root element found in XML file.\n");
		return nullptr;
	}
}
