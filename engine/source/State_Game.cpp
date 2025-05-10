#include "../include/State_Game.h"

void State_Game::OnCreate()
{
	m_type = StateType::Game;
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();
	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;

	m_rectBackground.setSize(sf::Vector2f(windowSize));
	m_rectBackground.setPosition(0, 0);
	m_rectBackground.setFillColor(sf::Color(40, 130, 40, 255));

	

	textureManager->RequireResource("Crosshairs");
	m_spriteCrosshairs.setTexture(*textureManager->GetResource("Crosshairs"));
	m_spriteCrosshairs.setOrigin(textureManager->GetResource("Crosshairs")->getSize().x / 2.0f, textureManager->GetResource("Crosshairs")->getSize().y / 2.0f);
	m_spriteCrosshairs.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_stateManager->GetContext()->m_entityManager->CreateEntity(EntityType::Player);
	m_stateManager->GetContext()->m_hudManager->CreateHUD();
}

void State_Game::OnDestroy()
{
	m_stateManager->GetContext()->m_entityManager->GetPlayer()->MarkForDeletion();
}

void State_Game::Activate()
{
	
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->setMouseCursorVisible(false);
}

void State_Game::Deactivate()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->setMouseCursorVisible(true);
	m_stateManager->GetContext()->m_entityManager->GetPlayer()->ResetMove();
}

void State_Game::Update(const sf::Time& l_deltaTime)
{
	sf::Vector2i mousePosition = m_stateManager->GetContext()->m_eventManager->GetMousePosition();
	m_spriteCrosshairs.setPosition(mousePosition.x, mousePosition.y);

	m_stateManager->GetContext()->m_entityManager->Update(l_deltaTime.asSeconds());
	m_stateManager->GetContext()->m_hudManager->Update(l_deltaTime.asSeconds());
	
	if (m_stateManager->GetContext()->m_entityManager->GetPlayer()->GetHitPoints() <= 0)
		m_stateManager->GetContext()->m_stateManager->SwitchTo(StateType::GameOver);
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_rectBackground);
	m_stateManager->GetContext()->m_entityManager->Draw();
	m_stateManager->GetContext()->m_hudManager->Draw();
	window->draw(m_spriteCrosshairs);
}

void State_Game::Pause()
{
	m_stateManager->SwitchTo(StateType::Paused);
}

void State_Game::Store()
{
	m_stateManager->SwitchTo(StateType::Store);
}

void State_Game::GameOver()
{
	m_stateManager->SwitchTo(StateType::Intro);
}

