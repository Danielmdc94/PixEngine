#pragma once

#include "BaseState.h"
#include "StateManager.h"
#include "EventManager.h"
#include "UILayer_EngineMenu.h"

class State_EngineMenu : public BaseState
{
public:
	State_EngineMenu(StateManager* l_stateManager) : BaseState(l_stateManager)
	{
		CreateUILayer();
	}
	
	void OnCreate() override;
	void OnDestroy() override;
	
	void Activate() override;
	void Deactivate() override;
	
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;
	
	void HandleClick(EventDetails* details) override;
	void HandleMouseMove(EventDetails* details) override;

private:
	UILayer_EngineMenu* GetMenuUILayer() const;
};
