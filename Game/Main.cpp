#include "Node.h"
#include "MainLoop.h"
#include "SceneTree.h"
#include "core/Color.h"
#include "engine/manager/InputManager.h"
#include "engine/manager/AudioManager.h"
#include "engine/manager/RenderManager.h"
//#include "vld.h"


class World : public Node {
public:
	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override {
		Node::SerializeToXML(element, doc);
	}

	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override {
		Node::DeserializeFromXML(element);
	}

	virtual void _Update(float dt) override {
		if (InputManager::GetInstance()->IsKeyPressed(KEY_SPACE))
		{
			SceneTree::GetInstance()->SaveCurrentSceneToXML(GAME_SCENE_FILE);
		}
	}

	virtual void _Render() override {
		// Test rendering
		RenderManager::GetInstance()->DrawText("Hello World", 200, 10, 20, PURPLE);
		RenderManager::GetInstance()->DrawRectangle(10, 50, 100, 50, RED);
		RenderManager::GetInstance()->DrawCircle(100, 100, 50, BLUE);
		RenderManager::GetInstance()->DrawLine(0, 0, 200, 200, GREEN);
		RenderManager::GetInstance()->DrawLine(200, 0, 0, 200, GREEN);
		RenderManager::GetInstance()->DrawRectangleLines(10, 50, 100, 50, BLACK);
		RenderManager::GetInstance()->DrawCircleLines(100, 100, 50, BLACK);
		RenderManager::GetInstance()->DrawTexture("assets/texture/Silksong.jpg", 200, 200, 0.0f, 0.2f, WHITE);
	}
};
REGISTER_NODE_CLASS(World);

int main() {

	if (SceneTree::GetInstance()->LoadSceneFromXML(GAME_SCENE_FILE)) {
		printf("Scene loaded successfully\n");
	}
	else
	{
		printf("Failed to load scene\n");
		printf("Creating a new scene manually\n");

		Scene* scene = new Scene();
		scene->SetName("MainScene");

		World* world = new World();

		scene->AddChild(world);

		SceneTree::GetInstance()->AddScene(scene);
	}

	//Run the main loop
	MainLoop::GetInstance()->Run();
}