#include "../include/Character.h"
#include "../include/EntityManager.h"
#include "../include/SharedContext.h"
#include <iostream>

Character::Character(EntityManager* l_entityManager) : Entity(l_entityManager)
{
	m_name = "Character";
	m_isHurt = false;
}

Character::~Character()
{

}

void Character::MoveInDirection(const Direction& l_dir)
{
	bool didMove = false;

	if (l_dir == Direction::Up)
	{
		Accelerate(0, -m_speed.y);
		didMove = true;
	}
	else if (l_dir == Direction::Down)
	{
		Accelerate(0, m_speed.y);
		didMove = true;
	}
	else if (l_dir == Direction::Left)
	{
		Accelerate(-m_speed.x, 0);
		didMove = true;
	}
	else if (l_dir == Direction::Right)
	{
		Accelerate(m_speed.x, 0);
		didMove = true;
	}
	if (didMove && GetState() == EntityState::Idle)
	{
		SetState(EntityState::Moving);
	}
}

int Character::GetMaxHitPoints()
{
	return m_maxHitPoints;
}

void Character::SetMaxHitpoints(int l_maxHitPoints)
{
	m_maxHitPoints = l_maxHitPoints;
}

int Character::GetHitPoints()
{
	return m_hitPoints;
}

void Character::SetHitpoints(int l_hitPoints)
{
	if (l_hitPoints < 0)
		l_hitPoints = 0;
	if (l_hitPoints > m_maxHitPoints)
		l_hitPoints = m_maxHitPoints;
	m_hitPoints = l_hitPoints;
}

void Character::Update(float l_deltaTime)
{
	Entity::Update(l_deltaTime);
	if (abs(m_velocity.x) >= 0.1f || abs(m_velocity.y) >= 0.1f)
		SetState(EntityState::Moving);
	else
		SetState(EntityState::Idle);
	m_sprite.setPosition(m_position);
	m_boxCollider = Rectangle(sf::Vector2f(GetSize().x - 34, GetSize().y - 14), GetPosition());
}

void Character::Draw(sf::RenderWindow* l_window)
{
	if (m_isHurt)
		FlashSprite(&m_sprite, sf::Color::Red, &m_isHurt);
	l_window->draw(m_sprite);
}

bool Character::TakeDamage(int l_damage)
{
	if (m_isHurt)
		return false;
	m_isHurt = true;
	SetHitpoints(GetHitPoints() - l_damage);
	m_flashTimer.restart();
	return true;
}

void Character::FlashSprite(sf::Sprite* l_sprite, sf::Color l_color, bool* l_condition)
{
	if (m_flashTimer.getElapsedTime().asSeconds() < 0.1f)
		l_sprite->setColor(l_color);
	else
	{
		l_sprite->setColor(sf::Color::White);
		if (l_condition)
			*l_condition = false;
	}
}
