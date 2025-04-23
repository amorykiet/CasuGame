#pragma once
#include "Singleton.h"
#include "Entity.h"
#include <vector>
#include <string>

class EntityManager : public Singleton<EntityManager>
{
public:
	void AddEntity(Entity* entity)
	{
		m_entities.push_back(entity);
	}

	void RemoveEntity(Entity* entity)
	{
		entity->Destroy();
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());

		delete entity;
	}

	void Update(double deltaTime)
	{
		for (auto entity : m_entities)
		{
			if (entity->IsActive())
			{
				entity->Update(deltaTime);
			}
		}
	}

	void Render()
	{
		for (auto entity : m_entities)
		{
			if (entity->IsActive())
			{
				entity->Render();
			}
		}
	}

	void Init()
	{

		for (auto entity : m_entities)
		{
			entity->Init();
		}
	}

	void Destroy()
	{
		for (auto entity : m_entities)
		{
			entity->Destroy();
			delete entity;
		}
		m_entities.clear();
	}

private:
	std::vector<Entity*> m_entities;
};
