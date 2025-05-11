#pragma once

#include <SFML/Graphics.hpp>

enum class EntityType { Base };

enum class EntityState { Idle, Moving };

enum class Direction { Up, Down, Left, Right };

class EntityManager;

class Entity
{
	friend class EntityManager;
public:
	Entity(EntityManager* l_entityManager);
	virtual ~Entity();

	void SetPosition(const float& l_x, const float& l_y);
	void SetPosition(const sf::Vector2f& l_pos);
	void SetSize(const float& l_x, const float& l_y);
	void SetState(const EntityState& l_state);

	std::string GetName() { return m_name; };
	unsigned int GetId() { return m_id; };
	EntityType GetType() { return m_type; };
	EntityState GetState() { return m_state; };
	sf::Vector2f GetPosition() { return m_position; };
	sf::Vector2f GetSize() { return m_size; };

	bool IsMarkedForDeletion() const { return m_isMarkedForDeletion; }
	void MarkForDeletion() { m_isMarkedForDeletion = true; }

	void Move(float l_x, float l_y);
	void Move(sf::Vector2f l_newPosition);
	void AddVelocity(float l_x, float l_y);
	void Accelerate(float l_x, float l_y);
	void SetAcceleration(float l_x, float l_y);
	void ApplyFriction(float l_x, float l_y);
	virtual void Update(float l_deltaTime);
	virtual void Draw(sf::RenderWindow* l_wind) = 0;

protected:

	bool m_isMarkedForDeletion;

	std::string m_name;
	EntityType m_type;
	unsigned int m_id;
	sf::Vector2f m_position;
	sf::Vector2f m_positionOld;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_friction;
	sf::Vector2f m_size;

	EntityState m_state;
	
	EntityManager* m_entityManager;
};

