#include "World.h"
#include "manager/InputManager.h"
#include "SceneTree.h"
#include "Enemy.h"
#include "Collision.h"
#include "MainLoop.h"
#include "manager/RenderManager.h"
#include "manager/CollisionManager.h"

// Add a timer member to World
// (Add this to World class definition in World.h: float enemySpawnTimer = 0.0f; const float enemySpawnInterval = 4.0f;)

void World::SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) {
	Node::SerializeToXML(element, doc);
}

void World::DeserializeFromXML(tinyxml2::XMLElement* element) {
	Node::DeserializeFromXML(element);
}

void World::_Ready()
{
	if (HasChildWithType("Player"))
	{
		player = dynamic_cast<Player*>(GetChildByType("Player"));
	}
	else
	{
		player = new Player();
		AddChild(player);
	}
	enemySpawnTimer = 0.0f;
}

void World::_Update(float dt) {
	if (InputManager::GetInstance()->IsKeyPressed(KEY_K)) {
		SceneTree::GetInstance()->SaveCurrentSceneToXML(GAME_SCENE_FILE);
	}

	if (!isPlaying)
	{
		RenderManager::GetInstance()->DrawText("Player Hit!", 10, 10, 70, YELLOW);
		RenderManager::GetInstance()->DrawText("Space to restart", 10, 100, 50, YELLOW);
		if (InputManager::GetInstance()->IsKeyPressed(KEY_SPACE)) {
			isPlaying = true;		
			player = new Player();
			AddChild(player);

			// Clear all enemies
			for (Enemy* enemy : enemies) {
				if (!enemy->isDestroyed()) {
					RemoveChild(enemy);
				}
			}
			enemies.clear();
		}
		return;
	}

	// Check enemies out of window
	for (size_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->isDestroyed()) {
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}

	enemySpawnTimer += dt;
	if (enemySpawnTimer >= enemySpawnInterval) {
		enemySpawnTimer = 0.0f;
		Enemy* enemy = new Enemy();
		//Spawn random position of enemy outside the window then move it toward player
		int windowWidth = MainLoop::GetInstance()->GetWidth();
		int windowHeight = MainLoop::GetInstance()->GetHeight();

		float x = 0, y = 0;
		if (GetRandomValue(0, 1) == 0)
		{
			x = (float) GetRandomValue(0, windowWidth);
			y = GetRandomValue(0, 1) == 0 ? -20 : windowHeight + 20;
		}
		else
		{
			y = (float) GetRandomValue(0, windowHeight);
			x = GetRandomValue(0, 1) == 0 ? -20 : windowWidth + 20;
		}
		RVector2 direction = { player->GetPosition().x - x, player->GetPosition().y - y };
		direction = direction.Normalize();
		enemy->SetPosition({ x, y });
		enemy->SetDirection(direction);
		enemy->SetSpeed(GetRandomValue(200.0f, 400.0f));
		enemy->SetPlayerHitCallback(std::bind(&World::OnPlayerHit, this));

		AddChild(enemy);
		enemies.push_back(enemy);
	}
}

void World::OnPlayerHit()
{
	RemoveChild(player);
	// Reset player position
	isPlaying = false;
}