#pragma once
#include "Node.h"
#include "Collision.h"
#include "core/Vector2.h"

class Player : public Node {
public:
    virtual void _SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override;
    virtual void _DeserializeFromXML(tinyxml2::XMLElement* element) override;
	virtual void _ShowInspector() override;
    virtual void _Ready() override;
    virtual void _Update(float dt) override;
    virtual void _Render() override;
    virtual void _Destroy() override;

    RVector2 GetPosition();

private:
    RVector2 position;
    RVector2 collisionOffset;
	float size = 25.0f;
    Collision* collision;
};

REGISTER_NODE_CLASS(Player);
