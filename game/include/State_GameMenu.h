#pragma once

#include "BaseState.h"
#include "StateManager.h"
#include "EventManager.h"
#include "UILayer_GameMenu.h"

class State_GameMenu : public BaseState
{
public:
	State_GameMenu(StateManager* l_stateManager) : BaseState(l_stateManager) {}
	
	void OnCreate() override;
	void OnDestroy() override;
	
	void Activate() override;
	void Deactivate() override;
	
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;
};
