#include "../include/State_Intro.h"

void State_Intro::OnCreate()
{
	m_type = StateType::Intro;
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();
	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;
	AudioManager* audioManager = m_stateManager->GetContext()->m_audioManager;
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;


	audioManager->RequireResource("LogoSFX");
	m_sfxLogo = audioManager->GetResource("LogoSFX");
	m_sfxLogo->setVolume(10);

	textureManager->RequireResource("Logo_256");
	m_spriteLogo.setTexture(*textureManager->GetResource("Logo_256"));
	m_spriteLogo.setOrigin(m_spriteLogo.getTexture()->getSize().x / 2.0f, m_spriteLogo.getTexture()->getSize().y / 2.0f);
	m_spriteLogo.setPosition(windowSize.x / 2.0f, windowSize.y / 3.0f);
	m_spriteLogo.setColor(sf::Color(255, 255, 255, 0));

	fontManager->RequireResource("EngineFont");

	m_textLogo.setFont(*fontManager->GetResource("EngineFont"));
	m_textLogo.setString(sf::String("PixEngine"));
	m_textLogo.setCharacterSize(64);
	m_textLogo.setStyle(sf::Text::Bold);
	m_textLogo.setOutlineColor(sf::Color::Black);
	m_textLogo.setOutlineThickness(2.f);

	sf::FloatRect textRect = m_textLogo.getLocalBounds();
	m_textLogo.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_textLogo.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_textContinue.setFont(*fontManager->GetResource("EngineFont"));
	m_textContinue.setString(sf::String("Press any key to continue"));
	m_textContinue.setCharacterSize(32);
	m_textContinue.setOutlineColor(sf::Color::Black);
	m_textContinue.setOutlineThickness(1.f);

	textRect = m_textContinue.getLocalBounds();
	m_textContinue.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_textContinue.setPosition(windowSize.x / 2.0f, windowSize.y / 1.2f);

	m_timerSpriteLogo = 0.f;
	m_timerTextLogo = 0.f;
	m_timerTextContinue = 0.f;
	m_musicPlayed = false;
}

void State_Intro::OnDestroy()
{

}

void State_Intro::Activate()
{

}

void State_Intro::Deactivate()
{

}

void State_Intro::Update(const sf::Time& l_deltaTime)
{
	m_timerSpriteLogo += l_deltaTime.asSeconds();
	m_timerTextContinue += l_deltaTime.asSeconds();
	m_timerTextLogo += l_deltaTime.asSeconds();

	if (!m_musicPlayed)
	{
		m_sfxLogo->play();
		m_musicPlayed = true;
	}
	
}

void State_Intro::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	if (m_timerSpriteLogo <= 2.5f)
		m_spriteLogo.setColor(sf::Color(255, 255, 255, 255 * (m_timerSpriteLogo / 2.5f)));

	window->draw(m_spriteLogo);
	
	if (m_timerTextLogo >= 2.5f)
	{
		window->draw(m_textLogo);
		if (m_timerTextContinue <= 0.5f)
        		window->draw(m_textContinue);
        	if (m_timerTextContinue >= 1.f)
        		m_timerTextContinue = 0.f;
	}
}

void State_Intro::Continue()
{
	m_stateManager->SwitchTo(StateType::Game);
}
