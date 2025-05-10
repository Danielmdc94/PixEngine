#include "../include/State_Paused.h"

void State_Paused::OnCreate()
{
	m_type = StateType::Paused;
	SetTransparent(true);
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;

	fontManager->RequireResource("MainFont");

	m_textTitle.setFont(*fontManager->GetResource("MainFont"));
	m_textTitle.setString(sf::String("Paused"));
	m_textTitle.setCharacterSize(64);
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

	m_rectBackground.setSize(sf::Vector2f(windowSize));
	m_rectBackground.setPosition(0, 0);
	m_rectBackground.setFillColor(sf::Color(0, 0, 0, 150));
}

void State_Paused::OnDestroy()
{

}

void State_Paused::Activate()
{

}

void State_Paused::Deactivate()
{

}

void State_Paused::Update(const sf::Time& l_deltaTime)
{
	m_textTimer += l_deltaTime.asSeconds();
}

void State_Paused::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_rectBackground);
	window->draw(m_textTitle);
	if (m_textTimer <= 0.5f)
		window->draw(m_textContinue);
	if (m_textTimer >= 1.f)
		m_textTimer = 0.f;
}

void State_Paused::Unpause()
{
	m_stateManager->SwitchTo(StateType::Game);
}
