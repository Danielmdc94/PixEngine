#include "../include/Entity.h"
#include "../include/EntityManager.h"
#include "../include/SharedContext.h"


Entity::Entity(EntityManager* l_entityMgr) :
	m_entityManager(l_entityMgr), 
	m_name("Entity"),
	m_type(EntityType::Base),
	m_state(EntityState::Idle),
	m_id(0),
	m_isMarkedForDeletion(false)
{

}

Entity::~Entity()
{

}

void Entity::SetPosition(const float& l_x, const float& l_y)
{
	m_position = sf::Vector2f(l_x, l_y);
}

void Entity::SetPosition(const sf::Vector2f& l_pos)
{
	m_position = l_pos;
}

void Entity::SetSize(const float& l_x, const float& l_y)
{
	m_size = sf::Vector2f(l_x, l_y);
}

void Entity::SetState(const EntityState& l_state)
{
	m_state = l_state;
}

void Entity::SetAcceleration(float l_x, float l_y)
{
	m_acceleration = sf::Vector2f(l_x, l_y);
}


void Entity::Move(float l_x, float l_y)
{
	m_positionOld = m_position;
	m_position += sf::Vector2f(l_x, l_y);
	sf::FloatRect viewRect = m_entityManager->GetContext()->m_window->GetViewSpace();
	if (m_position.x < 0)
		m_position.x = 0;
	else if (m_position.x > (viewRect.width))
		m_position.x = (viewRect.width);
	if (m_position.y < 0)
		m_position.y = 0;
	else if (m_position.y > (viewRect.height))
		m_position.y = (viewRect.height);
}

void Entity::Move(sf::Vector2f l_newPosition)
{
	m_positionOld = m_position;
	m_position += l_newPosition;
	sf::FloatRect viewRect = m_entityManager->GetContext()->m_window->GetViewSpace();
	if (m_position.x < 0)
		m_position.x = 0;
	else if (m_position.x > (viewRect.width))
		m_position.x = (viewRect.width);
	if (m_position.y < 0)
		m_position.y = 0;
	else if (m_position.y > (viewRect.height))
		m_position.y = (viewRect.height);
}

void Entity::AddVelocity(float l_x, float l_y)
{
	m_velocity += sf::Vector2f(l_x, l_y);
	if (abs(m_velocity.x) > m_maxVelocity.x)
	{
		if (m_velocity.x < 0)
			m_velocity.x = -m_maxVelocity.x;
		else
			m_velocity.x = m_maxVelocity.x;
	}
	if (abs(m_velocity.y) > m_maxVelocity.y)
	{
		if (m_velocity.y < 0)
			m_velocity.y = -m_maxVelocity.y;
		else
			m_velocity.y = m_maxVelocity.y;
	}
}

void Entity::Accelerate(float l_x, float l_y)
{
	m_acceleration += sf::Vector2f(l_x, l_y);
}

void Entity::ApplyFriction(float l_x, float l_y)
{
	if (m_velocity.x != 0)
	{
		if (abs(m_velocity.x) - abs(l_x) < 0)
			m_velocity.x = 0;
		else
		{
			if (m_velocity.x < 0)
				m_velocity.x += l_x;
			else
				m_velocity.x -= l_x;
		}
	}
	if (m_velocity.y != 0)
	{
		if (abs(m_velocity.y) - abs(l_y) < 0)
			m_velocity.y = 0;
		else
		{
			if (m_velocity.y < 0)
				m_velocity.y += l_y;
			else
				m_velocity.y -= l_y;
		}
	}
}

void Entity::Update(float l_deltaTime)
{
	AddVelocity(m_acceleration.x * l_deltaTime, m_acceleration.y * l_deltaTime);
	SetAcceleration(0.0f, 0.0f);
	sf::Vector2f frictionValue;
	frictionValue = m_friction;
	float friction_x = (m_speed.x * frictionValue.x) * l_deltaTime;
	float friction_y = (m_speed.y * frictionValue.y) * l_deltaTime;
	ApplyFriction(friction_x, friction_y);
	sf::Vector2f deltaPos = m_velocity * l_deltaTime;
	Move(deltaPos.x, deltaPos.y);
}
