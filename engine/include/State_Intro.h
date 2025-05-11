#pragma once

#include "State.h"
#include "StateManager.h"
#include <SFML/Audio/Music.hpp>


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
	sf::Font m_font;
	sf::Sprite m_spriteLogo;
	sf::Text m_textLogo;
	sf::Text m_textContinue;
	sf::Music* m_sfxLogo;

	float m_timerTextContinue;
	float m_timerTextLogo;
	float m_timerSpriteLogo;

	bool m_musicPlayed;
};