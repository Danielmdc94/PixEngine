#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EntityManager.h"

#include "SharedContext.h"

class TileMap;


class Player : public Entity
{
public:
	Player(EntityManager* l_entityManager);
	virtual ~Player() = default;

	void Update(const sf::Time& l_deltaTime) override;
	void Draw(sf::RenderWindow* l_window) override;

	sf::Vector2f GetPosition() const { return m_shape.getPosition(); }

	void SetCollisionMap(TileMap* l_map) { m_collisionMap = l_map; }

	
private:
	void OnMoveUpPressed(EventDetails*)		{ m_moveUp = true; }
	void OnMoveDownPressed(EventDetails*)	{ m_moveDown = true; }
	void OnMoveLeftPressed(EventDetails*)	{ m_moveLeft = true; }
	void OnMoveRightPressed(EventDetails*)	{ m_moveRight = true; }
	void OnJumpPressed(EventDetails*)		{ m_jump = true; }
	
	void OnMoveUpReleased(EventDetails*)    { m_moveUp = false; }
	void OnMoveDownReleased(EventDetails*)  { m_moveDown = false; }
	void OnMoveLeftReleased(EventDetails*)  { m_moveLeft = false; }
	void OnMoveRightReleased(EventDetails*) { m_moveRight = false; }
	void OnJumpReleased(EventDetails*)		{ m_jump = false; }

	void ResolveCollision(sf::Vector2f& l_velocity, float l_deltaTime);


private:
	sf::RectangleShape m_shape;
	float m_speed;

	bool m_moveUp = false;
	bool m_moveDown = false;
	bool m_moveLeft = false;
	bool m_moveRight = false;
	bool m_jump = false;
	bool m_prevJump = false;

	// Physics state
	sf::Vector2f m_velocity{0.f, 0.f};
	bool m_onGround{false};

	// Movement tuning
	float m_maxSpeedX{350.f};
	float m_accelGround{6000.f};
	float m_decelGround{6500.f};
	float m_accelAir{4000.f};

	// Jumping and gravity tuning
	float m_gravity{2400.f};
	float m_fallGravityMultiplier{1.5f}; // stronger gravity when falling
	float m_jumpCutMultiplier{3.0f};     // stronger gravity when jump released early
	float m_jumpSpeed{900.f};

	// Coyote time and jump buffer (seconds)
	float m_coyoteTime{0.10f};
	float m_jumpBufferTime{0.12f};

	// Runtime timers
	float m_coyoteTimer{0.f};
	float m_jumpBufferTimer{0.f};

	TileMap* m_collisionMap = nullptr;

};
