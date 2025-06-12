#include "State_EngineMenu.h"

void State_EngineMenu::OnCreate()
{
	auto font = m_stateManager->GetContext()->m_fontManager->GetResource("EngineFont");
	if (font && GetMenuUILayer())
	{
		GetMenuUILayer()->SetupButtons(*font);
	}
	
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::EngineMenu, "Mouse_Left", &State_EngineMenu::HandleClick, this);
	eventManager->AddCallback(StateType::EngineMenu, "Mouse_Move", &State_EngineMenu::HandleMouseMove, this);
}

void State_EngineMenu::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::EngineMenu, "Mouse_Left");
	eventManager->RemoveCallback(StateType::EngineMenu, "Mouse_Move");
}

void State_EngineMenu::Activate()
{

}

void State_EngineMenu::Deactivate()
{

}

void State_EngineMenu::Update(const sf::Time& l_deltaTime)
{
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);

}

void State_EngineMenu::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window);
}

void State_EngineMenu::HandleClick(EventDetails* details)
{
	m_uiLayer->HandleClick(details);
}

void State_EngineMenu::HandleMouseMove(EventDetails* details)
{
	m_uiLayer->HandleMouseMove(details);
}

UILayer_EngineMenu* State_EngineMenu::GetMenuUILayer() const
{
	return static_cast<UILayer_EngineMenu*>(m_uiLayer.get());
}
