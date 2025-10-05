#include "UILayer_EngineMenu.h"
#include "StateManager.h"

void UILayer_EngineMenu::OnCreate()
{
	std::cout << "[OnCreate] this=" << this
			  << " m_elements.size=" << m_elements.size()
			  << " data=" << static_cast<const void*>(m_elements.data())
			  << "\n";

	UILayer::OnCreate();

	auto font = m_owner->GetStateManager()->GetContext()->m_fontManager->GetResource("EngineFont");
	
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
	
	std::cout << "[OnCreate end] this=" << this
			  << " m_elements.size=" << m_elements.size()
			  << " data=" << static_cast<const void*>(m_elements.data())
			  << "\n";

}

void UILayer_EngineMenu::PlayButton()
{
	std::cout << "Play button clicked! But there is nothing to play...\n";
}

void UILayer_EngineMenu::QuitButton()
{
	m_owner->GetStateManager()->SwitchTo(StateType::EngineIntro);
	m_owner->GetStateManager()->Remove(StateType::EngineMenu);
}
