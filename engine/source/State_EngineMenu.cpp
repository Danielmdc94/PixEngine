#include "State_EngineMenu.h"

void State_EngineMenu::OnCreate()
{
	CreateUILayer<UILayer_EngineMenu>();
}

void State_EngineMenu::OnDestroy()
{
	if (m_uiLayer)
	{
		m_uiLayer->OnDestroy();
		m_uiLayer = nullptr;
	}
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
