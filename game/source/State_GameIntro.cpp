#include "State_GameIntro.h"

#include "Player.h"
#include "EntityManager.h"

void State_GameIntro::OnCreate()
{
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	fontManager->RequireResource("EngineFont");
	m_textTitle.setFont(*fontManager->GetResource("EngineFont"));
	m_textTitle.setString(sf::String("Game Title"));
	m_textTitle.setCharacterSize(128);
	m_textTitle.setStyle(sf::Text::Bold);
	m_textTitle.setOutlineColor(sf::Color::Black);
	m_textTitle.setOutlineThickness(2.f);
	sf::FloatRect textRect = m_textTitle.getLocalBounds();
	m_textTitle.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_textTitle.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 4.0f);

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::GameIntro, "Key_Space", &State_GameIntro::Continue, this);
}

void State_GameIntro::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::GameIntro, "Key_Space");
	m_stateManager->GetContext()->m_entityManager->ClearEntities();
}

void State_GameIntro::Activate()
{
	
}

void State_GameIntro::Deactivate()
{
	
}

void State_GameIntro::Update(const sf::Time& l_deltaTime)
{
	m_stateManager->GetContext()->m_entityManager->Update(l_deltaTime);
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);
}

void State_GameIntro::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	m_stateManager->GetContext()->m_entityManager->Draw();
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window);

	window->draw(m_textTitle);
}

void State_GameIntro::Continue(EventDetails* l_details)
{
	m_stateManager->SwitchTo(StateType::GameMenu);
	m_stateManager->Remove(StateType::GameIntro);
}
