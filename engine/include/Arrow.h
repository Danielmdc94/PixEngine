#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class EntityManager;

class Arrow : public Entity
{
public:
	Arrow(EntityManager* l_entityManager);
	virtual ~Arrow();

	void Load();

	void Update(float l_deltaTime);
	void Draw(sf::RenderWindow* l_wind);

protected:
	sf::Sprite m_sprite;
	sf::FloatRect m_rect;
	sf::Vector2f m_direction;
};
