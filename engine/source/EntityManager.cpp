#include "EntityManager.h"
#include "SharedContext.h"
#include "Player.h"

EntityManager::EntityManager(SharedContext* context) : m_context(context)
{
	m_nextId = 0;
	RegisterEntity<Player>(GameEntityType::Player);
}

EntityManager::~EntityManager()
{
	ClearEntities();
}
 
void EntityManager::Update(const sf::Time& l_deltaTime)
{
	for (auto& [id, entity] : m_entities)
	{
		if (!entity->IsMarkedForDeletion())
		{
			entity->Update(l_deltaTime);
		}
	}

	for (auto it = m_entities.begin(); it != m_entities.end(); )
	{
		if (it->second->IsMarkedForDeletion())
			it = m_entities.erase(it);
		else
			++it;
	}
}

void EntityManager::Draw()
{
	for (auto& [id, entity] : m_entities)
	{
		if (!entity->IsMarkedForDeletion())
        {
			entity->Draw(GetContext()->m_window->GetRenderWindow());
        }
	}
}

Entity* EntityManager::CreateEntity(const EntityType& l_type)
{
	{
		auto it = m_entityFactory.find(l_type);
		if (it == m_entityFactory.end())
		{
			return nullptr;
		}
		Entity* entity = it->second();
		entity->m_id = NextId();
		m_entities[entity->GetId()] = std::unique_ptr<Entity>(entity);
		return entity;
	}
}

EntityID EntityManager::NextId()
{
	return m_nextId++;
}

void EntityManager::ClearEntities()
{
	m_entities.clear();
}

SharedContext* EntityManager::GetContext()
{
	return m_context;
}

Entity* EntityManager::GetEntity(EntityID id)
{
	auto it = m_entities.find(id);
	if (it != m_entities.end())
	{
		return it->second.get();
	}
	return nullptr;
}
