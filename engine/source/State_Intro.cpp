#include "../include/State_Intro.h"

void State_Intro::OnCreate()
{
	m_type = StateType::Intro;
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();
	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;
	AudioManager* audioManager = m_stateManager->GetContext()->m_audioManager;
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;


	audioManager->RequireResource("MainTheme");
	audioManager->GetResource("MainTheme")->setVolume(10);
	audioManager->GetResource("MainTheme")->setLoop(true);
	audioManager->GetResource("MainTheme")->play();

	textureManager->RequireResource("IntroBackground");
	m_spriteBackground.setTexture(*textureManager->GetResource("IntroBackground"));
	m_spriteBackground.setOrigin(textureManager->GetResource("IntroBackground")->getSize().x / 2.0f, textureManager->GetResource("IntroBackground")->getSize().y / 2.0f);
	m_spriteBackground.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	fontManager->RequireResource("MainFont");

	m_textTitle.setFont(*fontManager->GetResource("MainFont"));
	m_textTitle.setString(sf::String("PixEngine"));
	m_textTitle.setCharacterSize(128);
	m_textTitle.setStyle(sf::Text::Bold);
	m_textTitle.setOutlineColor(sf::Color::Black);
	m_textTitle.setOutlineThickness(2.f);

	sf::FloatRect textRect = m_textTitle.getLocalBounds();
	m_textTitle.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_textTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 4.0f);

	m_textContinue.setFont(*fontManager->GetResource("MainFont"));
	m_textContinue.setString(sf::String("Press any key to continue"));
	m_textContinue.setCharacterSize(32);
	m_textContinue.setOutlineColor(sf::Color::Black);
	m_textContinue.setOutlineThickness(1.f);
	m_textTimer = 0.f;

	textRect = m_textContinue.getLocalBounds();
	m_textContinue.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_textContinue.setPosition(windowSize.x / 2.0f, windowSize.y / 1.2f);
}

void State_Intro::OnDestroy()
{

}

void State_Intro::Activate()
{
	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;
	m_stateManager->GetContext()->m_entityManager->ClearEntities();
	sf::Vector2f viewSize = m_view.getSize();
	sf::Vector2u textureSize = textureManager->GetResource("IntroBackground")->getSize();
	sf::Vector2f scaleFactors;
	scaleFactors.x = viewSize.x / textureSize.x;
	scaleFactors.y = viewSize.y / textureSize.y;
	m_spriteBackground.setScale(scaleFactors);
}

void State_Intro::Deactivate()
{

}

void State_Intro::Update(const sf::Time& l_deltaTime)
{
	m_textTimer += l_deltaTime.asSeconds();
}

void State_Intro::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_spriteBackground);
	window->draw(m_textTitle);
	if (m_textTimer <= 0.5f)
		window->draw(m_textContinue);
	if (m_textTimer >= 1.f)
		m_textTimer = 0.f;
}

void State_Intro::Continue()
{
	m_stateManager->SwitchTo(StateType::Game);
}
