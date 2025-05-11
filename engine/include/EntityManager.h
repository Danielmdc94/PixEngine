#pragma once

#include "Entity.h"

struct SharedContext;

class EntityManager
{
public:
	EntityManager(SharedContext* context);
	~EntityManager();

	void Update(float l_deltaTime);
	void Draw();

	void CreateEntity(const EntityType& l_type);
	void ClearEntities();


	SharedContext* GetContext();

private:

	SharedContext* m_context;

	std::vector<std::unique_ptr<Entity>> m_entities;
};