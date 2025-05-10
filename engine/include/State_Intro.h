#pragma once

#include "State.h"
#include "StateManager.h"

class State_Intro : public State
{
public:
	State_Intro(StateManager* l_stateManager) : State(l_stateManager) {}

	void OnCreate() override;
	void OnDestroy();
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void Continue();

private:
	sf::Sprite m_spriteBackground;
	sf::Text m_textTitle;
	sf::Text m_textContinue;
	sf::Font m_font;

	float m_textTimer;
};