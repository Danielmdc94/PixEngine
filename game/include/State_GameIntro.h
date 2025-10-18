#pragma once

#include "BaseState.h"
#include "StateManager.h"
#include "EventManager.h"
#include <SFML/Audio/Music.hpp>

class State_GameIntro : public BaseState
{
public:
	State_GameIntro(StateManager* l_stateManager) : BaseState(l_stateManager) {}

	void OnCreate() override;
	void OnDestroy();
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void Continue(EventDetails* l_details);

private:
	sf::Text m_textTitle;
};