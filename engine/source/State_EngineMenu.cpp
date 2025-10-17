#include "State_EngineMenu.h"

void State_EngineMenu::OnCreate()
{
	CreateUILayer<UILayer_EngineMenu>();
	auto* player = GetStateManager()->GetContext()->m_entityManager->CreateEntity(GameEntityType::Player);
}

void State_EngineMenu::OnDestroy()
{
	ClearUILayer();
}

void State_EngineMenu::Activate()
{

}

void State_EngineMenu::Deactivate()
{

}

void State_EngineMenu::Update(const sf::Time& l_deltaTime)
{
	GetStateManager()->GetContext()->m_entityManager->Update(l_deltaTime);
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);
}

void State_EngineMenu::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	GetStateManager()->GetContext()->m_entityManager->Draw();
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window);
}
