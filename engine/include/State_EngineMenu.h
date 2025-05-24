#pragma once

#include "BaseState.h"
#include "StateManager.h"
#include "EventManager.h"
#include "UIButton.h"
#include <SFML/Audio/Music.hpp>


class State_EngineMenu : public BaseState
{
public:
	State_EngineMenu(StateManager* l_stateManager) : BaseState(l_stateManager) {}

	void OnCreate() override;
	void OnDestroy();
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;
	
	void HandleMouseClick(EventDetails* details);

private:
	sf::Font m_font;

};