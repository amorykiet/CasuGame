#pragma once
#include "../core/Rectangle.h"
#include "../core/Observer.h"
#include "Node.h"

#include <string>
#include <vector>
#include <functional>

class Collision: public Node {
public:
	using CollisionCallback = std::function<void(Collision&)>;// signal for collision events

	virtual ~Collision() = default;

	virtual void _Render() override;

	virtual void SerializeToXML(tinyxml2::XMLElement* element, tinyxml2::XMLDocument* doc) override;
	virtual void DeserializeFromXML(tinyxml2::XMLElement* element) override;
	virtual void _ShowInspector() override;
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

	void AddOnCollisionEnterCallback(CollisionCallback callback);
	void AddOnCollisionReleaseCallback(CollisionCallback callback);

private:
	RRectangle					m_collisionRec;
	int							m_layer;					// Layer that other check collision to
	std::vector<int>			m_masks;					// Mask of other that this can collide with
	std::vector<CollisionCallback>	m_onCollisionEnterCallbacks;	// Callbacks for collision enter
	std::vector<CollisionCallback>	m_onCollisionReleaseCallbacks;	// Callbacks for collision release
};

REGISTER_NODE_CLASS(Collision);