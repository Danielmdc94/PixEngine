#include "State_Game.h"

#include <algorithm>

#include "Player.h"
#include "EntityManager.h"

void State_Game::OnCreate()
{
	m_world = new World(this);
	m_world->OnCreate();
	m_worldView = GetStateManager()->GetContext()->m_window->GetRenderWindow()->getDefaultView();
	m_view = GetStateManager()->GetContext()->m_window->GetRenderWindow()->getDefaultView();

	m_stateManager->GetContext()->m_entityManager->RegisterEntity<Player>(GameEntityType::Player);
	m_stateManager->GetContext()->m_entityManager->CreateEntity(GameEntityType::Player);
}

void State_Game::OnDestroy()
{
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
	window->setView(m_worldView);
	Entity* player = GetStateManager()->GetContext()->m_entityManager->GetEntity(0);
	m_world->Update(l_deltaTime);
	GetStateManager()->GetContext()->m_entityManager->Update(l_deltaTime);
	UpdateCamera(dynamic_cast<Player*>(player)->GetPosition(), 1.f, l_deltaTime);

	window->setView(m_view);
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);
}

void State_Game::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->setView(m_worldView);
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
	window->draw(text);
	
	window->setView(m_view);
	window->draw(text);
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window); 
}

void State_Game::UpdateCamera(const sf::Vector2f& playerPos, float zoomDelta, sf::Time l_deltaTime)
{
	const float followSpeed = 4.f;
	sf::Vector2f currentCenter = m_worldView.getCenter();
	float t = followSpeed * l_deltaTime.asSeconds();
	t = std::min(t, 1.f);

	sf::Vector2f newCenter = currentCenter + (playerPos - currentCenter) * t;
	m_worldView.setCenter(newCenter);

	if (zoomDelta != 1.f)
	{
		m_worldView.zoom(zoomDelta);
	}
}

