#pragma once

#include <unordered_map>
#include <functional>

#include "Entity.h"

struct SharedContext;

enum class EntityType
{
	Entity = 0, Player, Enemy
};

using EntityContainer = std::unordered_map<EntityID, std::unique_ptr<Entity>>;

using EntityFactory = std::unordered_map<EntityType, std::function<Entity* (void)>>;

class EntityManager
{
public:
	EntityManager(SharedContext* context);
	~EntityManager();

	void Update(const sf::Time& l_deltaTime);
	void Draw();

	template<typename T>
	void RegisterEntity(const EntityType& l_type)
	{
		m_entityFactory[l_type] = [this]() -> Entity* { return new T(this); };
	}
	Entity* CreateEntity(const EntityType& l_type);
	EntityID NextId();
	void ClearEntities();

	SharedContext* GetContext();

private:
	SharedContext* m_context;
	EntityContainer m_entities;
	EntityFactory m_entityFactory;
	EntityID m_nextId;
};
