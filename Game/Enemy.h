#pragma once
#include "Node.h"
#include "Collision.h"

class Enemy : public Node {

public:
	using PlayerHit = std::function<void()>; // signal for player hit

    virtual void _SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override;
    virtual void _DeserializeFromXML(tinyxml2::XMLElement* element) override;
	virtual void _ShowInspector() override;
    virtual void _Ready() override;
    virtual void _Update(float dt) override;
    virtual void _Render() override;
    virtual void _Destroy() override;

    void SetPlayerHitCallback(PlayerHit callback);
    void NotifyPlayerHit();

    void SetPosition(RVector2 pos);
    void SetDirection(RVector2 dir);
    void SetSpeed(float spd);

    Collision* GetCollision();

	// callback for collision events
    void OnCollisionEnter(Collision& other);

private:
	std::string texturePath = "assets/texture/enemies/enemy0.png";
    Collision* collision;
	RVector2 position;
    RVector2 collisionOffset;
    int size = 20;
    RVector2 direction;
	float speed = 100.0f;
	PlayerHit playerHitCallback; // Callback for player hit
};

REGISTER_NODE_CLASS(Enemy);