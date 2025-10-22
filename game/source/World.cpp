#include "World.h"

#include "StateManager.h"
#include "Player.h"

void World::OnCreate()
{
	m_worldView = m_owner->GetStateManager()->GetContext()->m_window->GetRenderWindow()->getDefaultView();
	m_mapSize = sf::Vector2i(64, 32);
	m_tileSize = 64.f;
	m_tileMap2 = new TileMap(m_mapSize.x, m_mapSize.y, static_cast<unsigned>(m_tileSize));
	//m_owner->GetStateManager()->GetContext()->m_textureManager->RequireResource("BrickTile");
	m_tileMap2->LoadFromFile("Map.txt", nullptr);
	//Tile groundTile(m_owner->GetStateManager()->GetContext()->m_textureManager->GetResource("BrickTile"), sf::IntRect(0, 0, 250, 250), true, 1);
	//for (unsigned x = 0; x < m_tileMap2->GetWidth(); ++x)m_tileMap2->SetTile(x, m_tileMap2->GetHeight() - 1, groundTile);

	
	m_tileMap.resize(m_mapSize.x, std::vector<sf::RectangleShape>());
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		m_tileMap[x].resize(m_mapSize.y, sf::RectangleShape());
		for (int y = 0; y < m_mapSize.y; ++y)
		{
			m_tileMap[x][y].setSize({m_tileSize, m_tileSize});
			m_tileMap[x][y].setFillColor(sf::Color::Transparent);
			m_tileMap[x][y].setOutlineColor(sf::Color::White);
			m_tileMap[x][y].setOutlineThickness(1.f);
			m_tileMap[x][y].setPosition(x * m_tileSize, y * m_tileSize);
		}
	}

	

	
	m_tileSelector.setSize({m_tileSize, m_tileSize});
	m_tileSelector.setFillColor(sf::Color::Transparent);
	m_tileSelector.setOutlineColor(sf::Color::Green);
	m_tileSelector.setOutlineThickness(2.f);
	m_tileSelector.setPosition(0.f, 0.f);

	m_owner->GetStateManager()->GetContext()->m_entityManager->RegisterEntity<Player>(GameEntityType::Player);
	m_owner->GetStateManager()->GetContext()->m_entityManager->CreateEntity(GameEntityType::Player);
}

void World::OnDestroy()
{
	m_tileMap.clear();
}

void World::Draw(sf::RenderWindow* l_window)
{
	l_window->setView(m_worldView);
	m_tileMap2->Draw(l_window);
	
	for (int x = std::max((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).x) / 64) - 3, 0); x < std::min((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).x) / 64) + 4, m_mapSize.x); ++x)
	{
		m_tileMap[x].resize(m_mapSize.y, sf::RectangleShape());
		for (int y = std::max((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).y) / 64) - 3, 0); y < std::min((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).y) / 64) + 4, m_mapSize.y ); ++y)
		{
			l_window->draw(m_tileMap[x][y]);
		}
	}
	
	l_window->draw(m_tileSelector);
}

void World::Update(sf::Time l_deltaTime)
{
	sf::RenderWindow* window = m_owner->GetStateManager()->GetContext()->m_window->GetRenderWindow();
	window->setView(m_worldView);
	
	sf::Vector2f mouseWorld = m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(window);
	m_owner->GetStateManager()->GetContext()->m_entityManager->Update(l_deltaTime);
	Entity* player = m_owner->GetStateManager()->GetContext()->m_entityManager->GetEntity(0);
	UpdateCamera(dynamic_cast<Player*>(player)->GetPosition(), 1.f, l_deltaTime);

	
	const float size = m_tileSize;
	sf::Vector2f snapped(std::floor(mouseWorld.x / size) * size, std::floor(mouseWorld.y / size) * size);
	m_tileSelector.setPosition(snapped);
}

void World::UpdateCamera(const sf::Vector2f& playerPos, float zoomDelta, sf::Time l_deltaTime)
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
