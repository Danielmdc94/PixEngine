#include "../include/EntityManager.h"
#include "../include/SharedContext.h"

#include <iostream>

EntityManager::EntityManager(SharedContext* context) : m_context(context)
{
	
}

EntityManager::~EntityManager()
{

}

void EntityManager::Update(float l_deltaTime)
{
	for (const auto& entity : m_entities)
	{
		entity->Update(l_deltaTime);
	}

	std::erase_if(m_entities, [](const std::unique_ptr<Entity>& entity)
		{
			return entity->IsMarkedForDeletion();
		});
}

void EntityManager::Draw()
{
	for (const auto& entity : m_entities)
	{
		entity->Draw(GetContext()->m_window->GetRenderWindow());
	}
}

void EntityManager::CreateEntity(const EntityType& l_type)
{
	std::unique_ptr<Entity> newEntity = nullptr;
	/*if (l_type == EntityType::Player)
	{
		newEntity = std::make_unique<Player>(this);
	}
	else
		return;*/

	m_entities.push_back(std::move(newEntity));
}

void EntityManager::ClearEntities()
{
	m_entities.clear();
}

SharedContext* EntityManager::GetContext()
{
	return m_context;
}
