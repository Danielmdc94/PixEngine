#pragma once

#include "Player.h"

Player::Player(EntityManager* l_entityManager) : Entity(l_entityManager), m_speed(200.f)
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

void Player::Update(const sf::Time& l_deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (m_moveUp)    movement.y -= m_speed * l_deltaTime.asSeconds();
	if (m_moveDown)  movement.y += m_speed * l_deltaTime.asSeconds();
	if (m_moveLeft)  movement.x -= m_speed * l_deltaTime.asSeconds();
	if (m_moveRight) movement.x += m_speed * l_deltaTime.asSeconds();

	m_shape.move(movement);
}

void Player::Draw(sf::RenderWindow* l_window)
{
	l_window->draw(m_shape);
}
