#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player : public Entity
{
public:
	Player(EntityManager* l_entityManager) : Entity(l_entityManager), m_speed(200.f)
	{
		m_name = "Player";

		m_shape.setSize({50.f, 50.f});
		m_shape.setFillColor(sf::Color::Cyan);
		m_shape.setOrigin(m_shape.getSize() / 2.f);
		m_shape.setPosition(400.f, 300.f);

		EventManager* eventManager = l_entityManager->GetContext()->m_eventManager;
		StateType state = eventManager->GetCurrentState();
		eventManager->AddCallback(state, "Move_Up_Press", &Player::OnMoveUpPressed, this);
		eventManager->AddCallback(state, "Move_Up_Release", &Player::OnMoveUpReleased, this);
		eventManager->AddCallback(state, "Move_Down_Press", &Player::OnMoveDownPressed, this);
		eventManager->AddCallback(state, "Move_Down_Release", &Player::OnMoveDownReleased, this);
		eventManager->AddCallback(state, "Move_Left_Press", &Player::OnMoveLeftPressed, this);
		eventManager->AddCallback(state, "Move_Left_Release", &Player::OnMoveLeftReleased, this);
		eventManager->AddCallback(state, "Move_Right_Press", &Player::OnMoveRightPressed, this);
		eventManager->AddCallback(state, "Move_Right_Release", &Player::OnMoveRightReleased, this);
	}

	void Update(const sf::Time& l_deltaTime) override
	{
		sf::Vector2f movement(0.f, 0.f);

		if (m_moveUp)    movement.y -= m_speed * l_deltaTime.asSeconds();
		if (m_moveDown)  movement.y += m_speed * l_deltaTime.asSeconds();
		if (m_moveLeft)  movement.x -= m_speed * l_deltaTime.asSeconds();
		if (m_moveRight) movement.x += m_speed * l_deltaTime.asSeconds();

		m_shape.move(movement);
	}


	void Draw(sf::RenderWindow* l_window) override
	{
		l_window->draw(m_shape);
	}
private:
	// Event callbacks: press
	void OnMoveUpPressed(EventDetails*)    { m_moveUp = true; }
	void OnMoveDownPressed(EventDetails*)  { m_moveDown = true; }
	void OnMoveLeftPressed(EventDetails*)  { m_moveLeft = true; }
	void OnMoveRightPressed(EventDetails*) { m_moveRight = true; }

	// Event callbacks: release
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
