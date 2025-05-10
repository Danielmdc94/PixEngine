#pragma once

#include "Character.h"
#include "Player.h"
#include "Arrow.h"
#include "Skeleton.h"

struct SharedContext;

class EntityManager
{
public:
	EntityManager(SharedContext* context);
	~EntityManager();

	void Update(float l_deltaTime);
	void Draw();

	Player* GetPlayer();
	std::vector<std::unique_ptr<Arrow>>& GetArrows();
	std::vector<std::unique_ptr<Skeleton>>& GetSkeletons();

	void CreateEntity(const EntityType& l_type);
	void ClearEntities();

	void SkeletonSpawner(float l_deltaTime);
	void ResetSkeletonSpawner();

	SharedContext* GetContext();

private:

	SharedContext* m_context;

	std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<std::unique_ptr<Arrow>> m_arrows;
	std::vector<std::unique_ptr<Skeleton>> m_skeletons;

	Player* m_player;

	float m_skeletonCooldown;
	float m_nextSkeletonCooldown;
	int m_spawnCount;
	int m_spawnWave;
};