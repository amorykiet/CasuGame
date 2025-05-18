#pragma once
#include "Node.h"
#include "Player.h"
#include "Enemy.h"

class World : public Node {
public:
	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override;
	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override;
	virtual void _Ready() override;
	virtual void _Update(float dt) override;

	void OnPlayerHit();

private:
	bool isPlaying = true;

	Player* player;
	std::vector<Enemy*> enemies;
	float enemySpawnTimer = 0.0f;
	const float enemySpawnInterval = 0.5f; // Time interval for spawning enemies
};
REGISTER_NODE_CLASS(World);
