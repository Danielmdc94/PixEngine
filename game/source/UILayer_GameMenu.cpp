#include "UILayer_GameMenu.h"
#include "StateManager.h"

void UILayer_GameMenu::OnCreate()
{
	UILayer::OnCreate();

	sf::Font* font = m_owner->GetStateManager()->GetContext()->m_fontManager->GetResource("EngineFont");
	
	UIButton* playButton = CreateElement<UIButton>();
	playButton->SetPosition({100.f, 100.f});
	playButton->SetSize({200.f, 50.f});
	playButton->SetText("Play", *font, 32);
	playButton->SetCallback([this]() { PlayButton(); });

	UIButton* quitButton = CreateElement<UIButton>();
	quitButton->SetPosition({100.f, 170.f});
	quitButton->SetSize({200.f, 50.f});
	quitButton->SetText("Quit", *font, 32);
	quitButton->SetCallback([this]() { QuitButton(); });
}

void UILayer_GameMenu::PlayButton()
{
	m_owner->GetStateManager()->SwitchTo(StateType::Game);
	m_owner->GetStateManager()->Remove(StateType::GameMenu);
}

void UILayer_GameMenu::QuitButton()
{
	m_owner->GetStateManager()->SwitchTo(StateType::GameIntro);
	m_owner->GetStateManager()->Remove(StateType::GameMenu);
}
