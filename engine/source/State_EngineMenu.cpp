#include "State_EngineMenu.h"

void State_EngineMenu::OnCreate()
{
	UIButton* playButton = m_uiLayer.CreateElement<UIButton>();
	playButton->SetPosition({100, 100});
	playButton->SetSize({200, 50});
	playButton->SetText("Play", *m_stateManager->GetContext()->m_fontManager->GetResource("EngineFont"));
	playButton->SetCallback([]() { std::cout << "Play button clicked!\n"; });


	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::EngineMenu, "Mouse_Left", &State_EngineMenu::HandleClick, this);
}

void State_EngineMenu::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::EngineIntro, "Mouse_Left");
}

void State_EngineMenu::Activate()
{

}

void State_EngineMenu::Deactivate()
{

}

void State_EngineMenu::Update(const sf::Time& l_deltaTime)
{
	m_uiLayer.Update(l_deltaTime);

}

void State_EngineMenu::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	m_uiLayer.Draw(*window);
}

void State_EngineMenu::HandleMouseMove(const sf::Vector2f& mousePos)
{
	m_uiLayer.HandleMouseMove(mousePos);
}

void State_EngineMenu::HandleClick(EventDetails* details)
{
	sf::Vector2f mousePos = details->m_mouse;
	m_uiLayer.HandleClick(mousePos);
}

