#pragma once

#include "State.h"
#include "StateManager.h"

class State_Game : public State
{
public:
	State_Game(StateManager* l_stateManager) : State(l_stateManager) {}

	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void Pause();
	void Store();
	void GameOver();

private:
	sf::RectangleShape m_rectBackground;

	sf::Sprite m_spriteCrosshairs;
};

