#pragma
#include "core/Entity.h"
#include "core/Color.h"
#include "core/Vector2.h"


class Circle : public Entity
{
public:
	Circle(RVector2 position, float radius, RColor color)
		: m_position(position), m_radius(radius), m_color(color)
	{
	}
	void Render() override
	{
		DrawCircleV(m_position, m_radius, m_color);
	}

	void Update(float deltaTime) override
	{
		m_position.x += 100.0f * deltaTime; // Move the circle to the right
	}

	void Destroy() override
	{
		// Cleanup logic for the circle (if any)
	}

private:
	RVector2 m_position;
	float m_radius;
	RColor m_color;
};