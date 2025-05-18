#include "MainLoop.h"
#include "SceneTree.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"

#include "vld.h"

int main() {
	Scene* scene = new Scene();
	scene->SetName("MainScene");

	World* world = new World();
	Player* player = new Player();

	world->AddChild(player);
	scene->AddChild(world);

	SceneTree::GetInstance()->AddScene(scene);
	//Run the main loop
	MainLoop::GetInstance()->Run();

}