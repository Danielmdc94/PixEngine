#pragma once

#include "BaseState.h"
#include "StateManager.h"
#include <SFML/Audio/Music.hpp>


class State_Intro : public BaseState
{
public:
	State_Intro(StateManager* l_stateManager) : BaseState(l_stateManager) {}

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

	float m_timePassed = 0.f;
	float m_timerTextContinue = 0.f;
	float m_timerTextLogo = 0.f;
	float m_timerSpriteLogo = 0.f;

	bool m_musicPlayed;
};