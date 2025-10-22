#pragma once

#include "Player.h"

#include "TileMap.h"
#include "MathUtils.h"


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
	eventManager->AddCallback(state, "Jump_Press", &Player::OnJumpPressed, this);
	eventManager->AddCallback(state, "Jump_Release", &Player::OnJumpReleased, this);
}

void Player::Update(const sf::Time& l_deltaTime)
{
    const float deltaTimeSeconds = l_deltaTime.asSeconds();
    if (deltaTimeSeconds <= 0.f) { return; }
    
    const int axisX = (m_moveRight ? 1 : 0) - (m_moveLeft ? 1 : 0);
    
    const bool jumpPressedThisFrame  = (m_jump && !m_prevJump);
    const bool jumpReleasedThisFrame = (!m_jump && m_prevJump);
    
    if (m_onGround)
    {
        m_coyoteTimer = m_coyoteTime;
    }
    else
    {
        m_coyoteTimer = std::max(0.f, m_coyoteTimer - deltaTimeSeconds);
    }
    
    if (jumpPressedThisFrame)
    {
        m_jumpBufferTimer = m_jumpBufferTime;
    }
    else
    {
        m_jumpBufferTimer = std::max(0.f, m_jumpBufferTimer - deltaTimeSeconds);
    }


    if (axisX != 0)
    {
        const float target = static_cast<float>(axisX) * m_maxSpeedX;
        const float accel = m_onGround ? m_accelGround : m_accelAir;
        m_velocity.x = Approach(m_velocity.x, target, accel * deltaTimeSeconds);
    }
    else
    {
        const float decel = m_onGround ? m_decelGround : m_accelAir;
        m_velocity.x = Approach(m_velocity.x, 0.f, decel * deltaTimeSeconds);
    }
    
    if (m_jumpBufferTimer > 0.f && m_coyoteTimer > 0.f)
    {
        m_velocity.y = -m_jumpSpeed;
        m_onGround = false;
        m_coyoteTimer = 0.f;
        m_jumpBufferTimer = 0.f;
    }
    
    float gravity = m_gravity;
    if (m_velocity.y < 0.f)
    {
        if (!m_jump)
        {
            gravity *= m_jumpCutMultiplier;
        }
    }
    else
    {
        gravity *= m_fallGravityMultiplier;
    }
    m_velocity.y += gravity * deltaTimeSeconds;
    
    if (jumpReleasedThisFrame && m_velocity.y < 0.f)
    {
        m_velocity.y *= 0.6f;
    }
    
    sf::Vector2f velToMove = m_velocity;
    ResolveCollision(velToMove, deltaTimeSeconds);
    
    m_velocity = velToMove;
    
    m_prevJump = m_jump;
}


void Player::Draw(sf::RenderWindow* l_window)
{
	l_window->draw(m_shape);
}

void Player::ResolveCollision(sf::Vector2f& l_velocity, float l_deltaTime)
{
    if (!m_collisionMap)
    {
        m_shape.move(l_velocity * l_deltaTime);
        m_onGround = false;
        return;
    }

    static constexpr float eps = 0.001f;

    const float tileSize = static_cast<float>(m_collisionMap->GetTileSize());
    sf::Vector2f pos = m_shape.getPosition();
    const sf::Vector2f half = m_shape.getSize() * 0.5f;
    
    bool groundedThisFrame = false;

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

        if (dx > 0.f)
        {
            int tx = txMax;
            bool hit = false;
            for (int ty = tyMin; ty <= tyMax; ++ty)
            {
                if (m_collisionMap->IsSolidAt(tx, ty))
                {
                    hit = true; break;
                }
            }
            if (hit)
            {
                float tileLeft = tx * tileSize;
                newCenterX = tileLeft - half.x;
                l_velocity.x = 0.f;
            }
        }
        else
        {
            int tx = txMin;
            bool hit = false;
            for (int ty = tyMin; ty <= tyMax; ++ty)
            {
                if (m_collisionMap->IsSolidAt(tx, ty))
                {
                    hit = true; break;
                }
            }
            if (hit)
            {
                float tileRight = (tx + 1) * tileSize;
                newCenterX = tileRight + half.x;
                l_velocity.x = 0.f;
            }
        }

        pos.x = newCenterX;
    }

    // Move on Y axis
    float dy = l_velocity.y * l_deltaTime;
    if (dy != 0.f)
    {
        float newCenterY = pos.y + dy;

        float left   = pos.x - half.x;
        float right  = pos.x + half.x;
        float top    = newCenterY - half.y;
        float bottom = newCenterY + half.y;

        int txMin = static_cast<int>(std::floor(left / tileSize));
        int txMax = static_cast<int>(std::floor((right - eps) / tileSize));
        int tyMin = static_cast<int>(std::floor(top / tileSize));
        int tyMax = static_cast<int>(std::floor((bottom - eps) / tileSize));

        if (dy > 0.f)
        { 
            int ty = tyMax;
            bool hit = false;
            for (int tx = txMin; tx <= txMax; ++tx)
            {
                if (m_collisionMap->IsSolidAt(tx, ty)) { hit = true; break; }
            }
            if (hit)
            {
                float tileTop = ty * tileSize;
                newCenterY = tileTop - half.y;
                l_velocity.y = 0.f;
                groundedThisFrame = true;
            }
        }
        else
        {
            int ty = tyMin;
            bool hit = false;
            for (int tx = txMin; tx <= txMax; ++tx)
            {
                if (m_collisionMap->IsSolidAt(tx, ty))
                {
                    hit = true; break;
                }
            }
            if (hit)
            {
                float tileBottom = (ty + 1) * tileSize;
                newCenterY = tileBottom + half.y;
                l_velocity.y = 0.f;
            }
        }
        pos.y = newCenterY;
    }

    m_shape.setPosition(pos);
    m_onGround = groundedThisFrame;
}


