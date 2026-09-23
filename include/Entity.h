#pragma once

#include <SFML/Graphics.hpp>

using EntityID = std::uint32_t;

class Entity
{
	friend class EntityManager;
public:
	Entity(EntityManager* l_entityManager) : m_entityManager(l_entityManager), m_name("Entity"), m_id(0), m_isMarkedForDeletion(false) {}
	virtual ~Entity() = default;

	std::string GetName() { return m_name; }
	EntityID GetId() { return m_id; }

	bool IsMarkedForDeletion() const { return m_isMarkedForDeletion; }
	void MarkForDeletion() { m_isMarkedForDeletion = true; }

	virtual void Update(const sf::Time& l_deltaTime) = 0;
	virtual void Draw(sf::RenderWindow* l_window) = 0;

protected:

	bool m_isMarkedForDeletion;

	std::string m_name;
	EntityID m_id;
	
	EntityManager* m_entityManager;
};

