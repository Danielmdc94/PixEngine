#include "State_GameMenu.h"

void State_GameMenu::OnCreate()
{
	std::cout << "TEST";
	CreateUILayer<UILayer_GameMenu>();
}

void State_GameMenu::OnDestroy()
{
	ClearUILayer();
}

void State_GameMenu::Activate()
{

}

void State_GameMenu::Deactivate()
{

}

void State_GameMenu::Update(const sf::Time& l_deltaTime)
{
	GetStateManager()->GetContext()->m_entityManager->Update(l_deltaTime);
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);
}

void State_GameMenu::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	GetStateManager()->GetContext()->m_entityManager->Draw();
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window);
}
