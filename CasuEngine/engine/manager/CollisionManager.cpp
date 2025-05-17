#include "CollisionManager.h"
#include <algorithm>

void CollisionManager::Update()
{	
	std::set<std::pair<Collision*, Collision*>> currentCollisions;
	// Check for collisions
	for (Collision* current : m_collisions)
	{
		for (Collision* target: m_collisions)
		{
			if (current == target) continue;
			if (current->CheckCollision(*target))
			{
				auto pair = std::minmax(current, target);
				currentCollisions.insert(pair);

				// Collision Enter
				if (m_lastCollisions.find(pair) == m_lastCollisions.end())
				{
					current->OnCollisionEnter(*target); // or onCollisionEnter
				}
			}
		}
	}

	// Collision Release
	for (const auto& pair : m_lastCollisions)
	{
		if (currentCollisions.find(pair) == currentCollisions.end())
		{
			if (pair.first->CheckMask(pair.second->GetLayer()))
			{
				pair.first->OnCollisionRelease(*pair.second);
			}
			
			if (pair.second->CheckMask(pair.first->GetLayer()))
			{
				pair.second->OnCollisionRelease(*pair.first);
			}
		}
	}

	m_lastCollisions = std::move(currentCollisions);
}

void CollisionManager::Close()
{
	m_collisions.clear();
}

bool CollisionManager::CheckCollisionRecs(RRectangle rec1, RRectangle rec2)
{
	return ::CheckCollisionRecs(rec1, rec2);
}

bool CollisionManager::CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
{
	return ::CheckCollisionCircles(center1, radius1, center2, radius2);
}

bool CollisionManager::CheckCollisionCircleRec(Vector2 center, float radius, RRectangle rec)
{
	return ::CheckCollisionCircleRec(center, radius, rec);
}

bool CollisionManager::CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2)
{
	return ::CheckCollisionCircleLine(center, radius, p1, p2);
}

bool CollisionManager::CheckCollisionPointRec(Vector2 point, RRectangle rec)
{
	return ::CheckCollisionPointRec(point, rec);
}

bool CollisionManager::CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius)
{
	return ::CheckCollisionPointCircle(point, center, radius);
}

bool CollisionManager::CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3)
{
	return ::CheckCollisionPointTriangle(point, p1, p2, p3);
}

bool CollisionManager::CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold)
{
	return ::CheckCollisionPointLine(point, p1, p2, threshold);
}

bool CollisionManager::CheckCollisionPointPoly(Vector2 point, const Vector2* points, int pointCount)
{
	return ::CheckCollisionPointPoly(point, points, pointCount);
}

bool CollisionManager::CheckCollisionLines(Vector2 startPos1, Vector2 endPos1,
	Vector2 startPos2,
	Vector2 endPos2,
	Vector2* collisionPoint)
{
	return ::CheckCollisionLines(startPos1,
		endPos1,
		startPos2,
		endPos2,
		collisionPoint);
}

RRectangle CollisionManager::GetCollisionRec(RRectangle rec1,
	RRectangle rec2)
{
	return ::GetCollisionRec(rec1,
		rec2);
}

void CollisionManager::AddCollision(Collision* collision)
{
	m_collisions.push_back(collision);
}

void CollisionManager::RemoveCollision(Collision* collision)
{
	m_collisions.erase(std::remove(m_collisions.begin(), m_collisions.end(), collision), m_collisions.end());
}