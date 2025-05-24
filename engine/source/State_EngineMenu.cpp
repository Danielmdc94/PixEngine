#include "State_EngineMenu.h"

void State_EngineMenu::OnCreate()
{
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;

	UIManager* uiManager = m_stateManager->GetContext()->m_uiManager;

	UIButton* backButton = uiManager->CreateElement<UIButton>("BackButton");
	backButton->SetPosition({100, 100});
	backButton->SetSize({200, 50});
	backButton->SetText("Play", *fontManager->GetResource("EngineFont"));
	backButton->SetCallback([]() {
		std::cout << "Back button clicked!\n";
	});

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::EngineMenu, "Mouse_Left", &State_EngineMenu::HandleMouseClick, this);
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

}

void State_EngineMenu::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
}

void State_EngineMenu::HandleMouseClick(EventDetails* details)
{
	sf::Vector2f mousePos(static_cast<float>(details->m_mouse.x), static_cast<float>(details->m_mouse.y));

	const auto* elements = m_stateManager->GetContext()->m_uiManager->GetElements();
	if (!elements) return;
	for (UIElement* element : *elements)
	{
		if (UIButton* button = dynamic_cast<UIButton*>(element))
		{
			if (button->IsVisible() && button->IsHovered(mousePos))
			{
				button->OnClick();
				break;
			}
		}
	}
}
