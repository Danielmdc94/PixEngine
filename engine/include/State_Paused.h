#pragma once

#include "State.h"
#include "StateManager.h"

class State_Paused : public State
{
public:
	State_Paused(StateManager* l_stateManager) : State(l_stateManager) {}

	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void Unpause();

private:
	sf::RectangleShape m_rectBackground;
	sf::Text m_textTitle;
	sf::Text m_textContinue;
	sf::Font m_font;

	float m_textTimer;
};