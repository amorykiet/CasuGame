#pragma once
#include "Node.h"
#include "Collision.h"

class Enemy : public Node {

public:
	using PlayerHit = std::function<void()>; // signal for player hit

    virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override;
    virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override;
	virtual void _ShowInspector() override;
    virtual void _Ready() override;
    virtual void _Update(float dt) override;
    virtual void _Render() override;
    virtual void _Destroy() override;

    void SetPlayerHitCallback(PlayerHit callback) { playerHitCallback = callback; }
    void NotifyPlayerHit() { if (playerHitCallback) playerHitCallback(); }

	void SetPosition(RVector2 pos) { position = pos; }
	void SetDirection(RVector2 dir) { direction = dir; }
	void SetSpeed(float spd) { speed = spd; }

	Collision* GetCollision() { return collision; }

	// callback for collision events
    void OnCollisionEnter(Collision& other);

private:
    Collision* collision;
	RVector2 position;
    int size = 20;
    RVector2 direction;
	float speed = 100.0f; // Speed of the enemy
	PlayerHit playerHitCallback; // Callback for player hit
};

REGISTER_NODE_CLASS(Enemy);