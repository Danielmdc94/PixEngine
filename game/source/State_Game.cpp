#include "State_Game.h"

#include <algorithm>

#include "EntityManager.h"

void State_Game::OnCreate()
{
	m_world = new World(this);
	m_world->OnCreate();
	m_view = GetStateManager()->GetContext()->m_window->GetRenderWindow()->getDefaultView();
}

void State_Game::OnDestroy()
{
	m_world->OnDestroy();
	ClearUILayer();
}

void State_Game::Activate()
{

}

void State_Game::Deactivate()
{

}

void State_Game::Update(const sf::Time& l_deltaTime)
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	m_world->Update(l_deltaTime);

	window->setView(m_view);
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	m_world->Draw(window);
	sf::Text text;
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setFont(*GetStateManager()->GetContext()->m_fontManager->GetResource("EngineFont"));
	text.setPosition(20.f, 20.f);

	std::stringstream ss;

	ss << "Screen: " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionScreen().x << " " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionScreen().y << "\n"
		<< "Window: " <<  GetStateManager()->GetContext()->m_eventManager->GetMousePositionWindow(window).x << " " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionWindow().y << "\n"
		<< "View: " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(window).x << " " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(window).y << "\n"
		<< "WorldTiles: " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(window).x / 64 << " " << GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(window).y / 64;

	text.setString(ss.str());
	
	GetStateManager()->GetContext()->m_entityManager->Draw();
	
	window->setView(m_view);
	window->draw(text);
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window); 
}
