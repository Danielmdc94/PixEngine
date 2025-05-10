#pragma once

#include "State.h"
#include "StateManager.h"

class State_GameOver : public State
{
public:
	State_GameOver(StateManager* l_stateManager) : State(l_stateManager) {}

	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void Restart();

private:
	sf::RectangleShape m_rectBackground;
	sf::Text m_textTitle;
	sf::Text m_textContinue;
	sf::Font m_font;

	float m_textTimer;
};