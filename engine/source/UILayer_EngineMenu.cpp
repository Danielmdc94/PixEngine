#include "UILayer_EngineMenu.h"
#include "StateManager.h"

void UILayer_EngineMenu::OnCreate()
{
	UILayer::OnCreate();

	auto font = m_owner->GetStateManager()->GetContext()->m_fontManager->GetResource("EngineFont");
	
	UIButton* playButton = CreateElement<UIButton>();
	playButton->SetPosition({100.f, 100.f});
	playButton->SetSize({200.f, 50.f});
	playButton->SetText("Play", *font, 32);
	playButton->SetCallback([]() { std::cout << "Play button clicked!\n"; });

	UIButton* quitButton = CreateElement<UIButton>();
	quitButton->SetPosition({100.f, 170.f});
	quitButton->SetSize({200.f, 50.f});
	quitButton->SetText("Quit", *font, 32);
	quitButton->SetCallback([]() { std::cout << "Quit button clicked!\n"; });
}
