#pragma once

#include "BaseState.h"
#include "Player.h"
#include "StateManager.h"
#include "World.h"

class State_Game : public BaseState
{
public:
	State_Game(StateManager* l_stateManager) : BaseState(l_stateManager) {}
	
	void OnCreate() override;
	void OnDestroy() override;
	
	void Activate() override;
	void Deactivate() override;

	sf::View* GetWorldView() { return &m_worldView; }
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;
	void UpdateCamera(const sf::Vector2f& playerPos, float zoomDelta, sf::Time l_deltaTime);

private:
	World* m_world;
	sf::View m_worldView;
};
