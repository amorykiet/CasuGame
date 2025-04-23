#pragma once

class Entity
{
public:
	virtual ~Entity() = default;
	// Entity lifecycle methods
	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
	virtual void Destroy() 
	{
		m_active = false;
	}
	// Entity state management
	void SetActive(bool active) { m_active = active; }
	bool IsActive() const { return m_active; }

protected:
	bool m_active{ true };

};