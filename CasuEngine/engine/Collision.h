#pragma once
#include "../core/Rectangle.h"
#include "../core/Observer.h"
#include "Node.h"

#include <string>
#include <vector>
#include <functional>

class Collision: public Node {
public:
	virtual ~Collision() = default;

	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override;
	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override;
	virtual void _Destroy() override;

	Collision();
	Collision(const RRectangle& rec);
	Collision(float x, float y, float width, float height);

	bool CheckCollision(const RRectangle& other);
	bool CheckCollision(const Collision& other);

	bool CheckMask(int layer);

	RRectangle GetCollisionRec();
	RRectangle GetCollisionRec(const Collision& other);

	void AddMask(int id);
	void RemoveMask(int id);
	void SetLayer(int id);
	int GetLayer() const;
	RVector2 GetSize() const;
	RVector2 GetPosition() const;
	void SetPosition(RVector2 pos);
	void SetSize(RVector2 size);

	void OnCollisionEnter(Collision& other);
	void OnCollisionRelease(Collision& other);

private:
	RRectangle					m_collisionRec;
	int							m_layer;					// Layer that other check collision to
	std::vector<int>			m_masks;					// Mask of other that this can collide with
};

REGISTER_NODE_CLASS(Collision);