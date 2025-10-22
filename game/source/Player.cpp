#pragma once

#include "Player.h"

#include "TileMap.h"

Player::Player(EntityManager* l_entityManager) : Entity(l_entityManager), m_speed(200.f)
{
	m_name = "Player";
	m_shape.setSize({48.f, 48.f});
	m_shape.setFillColor(sf::Color::Cyan);
	m_shape.setOrigin(m_shape.getSize() * 0.5f);
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
	const float deltaTimeSeconds = l_deltaTime.asSeconds();

	sf::Vector2f velocity(0.f, 0.f);


	if (m_moveUp)    velocity.y -= m_speed * deltaTimeSeconds;
	if (m_moveDown)  velocity.y += m_speed * deltaTimeSeconds;
	if (m_moveLeft)  velocity.x -= m_speed * deltaTimeSeconds;
	if (m_moveRight) velocity.x += m_speed * deltaTimeSeconds;

	m_shape.move(velocity);
	ResolveCollision(velocity, deltaTimeSeconds);
}

void Player::Draw(sf::RenderWindow* l_window)
{
	l_window->draw(m_shape);
}

void Player::ResolveCollision(sf::Vector2f& l_velocity, float l_deltaTime)
{
    // If there's no map, just move freely
    if (!m_collisionMap) {
        m_shape.move(l_velocity * l_deltaTime);
        return;
    }

    static constexpr float eps = 0.001f;

    const float tileSize = static_cast<float>(m_collisionMap->GetTileSize());
    sf::Vector2f pos = m_shape.getPosition();
    const sf::Vector2f half = m_shape.getSize() * 0.5f;

    // Move on X axis
    float dx = l_velocity.x * l_deltaTime;
    if (dx != 0.f) {
        float newCenterX = pos.x + dx;

        float left   = newCenterX - half.x;
        float right  = newCenterX + half.x;
        float top    = pos.y - half.y;
        float bottom = pos.y + half.y;

        int txMin = static_cast<int>(std::floor(left / tileSize));
        int txMax = static_cast<int>(std::floor((right - eps) / tileSize));
        int tyMin = static_cast<int>(std::floor(top / tileSize));
        int tyMax = static_cast<int>(std::floor((bottom - eps) / tileSize));

        if (dx > 0.f) {
            int tx = txMax;
            bool hit = false;
            for (int ty = tyMin; ty <= tyMax; ++ty) {
                if (m_collisionMap->IsSolidAt(tx, ty)) { hit = true; break; }
            }
            if (hit) {
                float tileLeft = tx * tileSize;
                newCenterX = tileLeft - half.x;
                l_velocity.x = 0.f; // stop horizontal velocity
            }
        } else {
            int tx = txMin;
            bool hit = false;
            for (int ty = tyMin; ty <= tyMax; ++ty) {
                if (m_collisionMap->IsSolidAt(tx, ty)) { hit = true; break; }
            }
            if (hit) {
                float tileRight = (tx + 1) * tileSize;
                newCenterX = tileRight + half.x;
                l_velocity.x = 0.f;
            }
        }

        pos.x = newCenterX;
    }

    // Move on Y axis
    float dy = l_velocity.y * l_deltaTime;
    if (dy != 0.f) {
        float newCenterY = pos.y + dy;

        float left   = pos.x - half.x;
        float right  = pos.x + half.x;
        float top    = newCenterY - half.y;
        float bottom = newCenterY + half.y;

        int txMin = static_cast<int>(std::floor(left / tileSize));
        int txMax = static_cast<int>(std::floor((right - eps) / tileSize));
        int tyMin = static_cast<int>(std::floor(top / tileSize));
        int tyMax = static_cast<int>(std::floor((bottom - eps) / tileSize));

        if (dy > 0.f) {
            int ty = tyMax;
            bool hit = false;
            for (int tx = txMin; tx <= txMax; ++tx) {
                if (m_collisionMap->IsSolidAt(tx, ty)) { hit = true; break; }
            }
            if (hit) {
                float tileTop = ty * tileSize;
                newCenterY = tileTop - half.y;
                l_velocity.y = 0.f;
            }
        } else {
            int ty = tyMin;
            bool hit = false;
            for (int tx = txMin; tx <= txMax; ++tx) {
                if (m_collisionMap->IsSolidAt(tx, ty)) { hit = true; break; }
            }
            if (hit) {
                float tileBottom = (ty + 1) * tileSize;
                newCenterY = tileBottom + half.y;
                l_velocity.y = 0.f;
            }
        }

        pos.y = newCenterY;
    }

    m_shape.setPosition(pos);
}

