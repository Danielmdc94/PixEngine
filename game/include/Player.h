#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EntityManager.h"

#include "SharedContext.h"

class Player : public Entity
{
public:
	Player(EntityManager* l_entityManager);
	~Player() = default;

	void Update(const sf::Time& l_deltaTime) override;
	void Draw(sf::RenderWindow* l_window) override;

	sf::Vector2f GetPosition() const { return m_shape.getPosition(); }
	
private:
	void OnMoveUpPressed(EventDetails*)    { m_moveUp = true; }
	void OnMoveDownPressed(EventDetails*)  { m_moveDown = true; }
	void OnMoveLeftPressed(EventDetails*)  { m_moveLeft = true; }
	void OnMoveRightPressed(EventDetails*) { m_moveRight = true; }
	
	void OnMoveUpReleased(EventDetails*)    { m_moveUp = false; }
	void OnMoveDownReleased(EventDetails*)  { m_moveDown = false; }
	void OnMoveLeftReleased(EventDetails*)  { m_moveLeft = false; }
	void OnMoveRightReleased(EventDetails*) { m_moveRight = false; }

private:
	sf::RectangleShape m_shape;
	float m_speed;

	bool m_moveUp{false};
	bool m_moveDown{false};
	bool m_moveLeft{false};
	bool m_moveRight{false};

};
