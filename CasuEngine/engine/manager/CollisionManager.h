#pragma once
#include "../core/Singleton.h"
#include "../core/Rectangle.h"
#include "Collision.h"
#include <vector>
#include <set>

class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Update();
	void Close();

	// Collision detection helper
    bool CheckCollisionRecs(RRectangle rec1, RRectangle rec2);       
    bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
    bool CheckCollisionCircleRec(Vector2 center, float radius, RRectangle rec);
    bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2);
    bool CheckCollisionPointRec(Vector2 point, RRectangle rec);
    bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
    bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);
    bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold);
    bool CheckCollisionPointPoly(Vector2 point, const Vector2* points, int pointCount);
    bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2* collisionPoint);
    RRectangle GetCollisionRec(RRectangle rec1, RRectangle rec2);

	// Collision management
	void AddCollision(Collision* collision);
	void RemoveCollision(Collision* collision);

private:
	std::vector<Collision*> m_collisions;
    std::set<std::pair<Collision*, Collision*>> m_lastCollisions;
};