#include "State_GameIntro.h"

#include "Player.h"
#include "EntityManager.h"

void State_GameIntro::OnCreate()
{
	GetStateManager()->GetContext()->m_entityManager->RegisterEntity<Player>(GameEntityType::Player);
	auto* player = GetStateManager()->GetContext()->m_entityManager->CreateEntity(GameEntityType::Player);
}

void State_GameIntro::OnDestroy()
{
	
}

void State_GameIntro::Activate()
{
	
}

void State_GameIntro::Deactivate()
{
	
}

void State_GameIntro::Update(const sf::Time& l_deltaTime)
{
	GetStateManager()->GetContext()->m_entityManager->Update(l_deltaTime);
	if (m_uiLayer)
		m_uiLayer->Update(l_deltaTime);
}

void State_GameIntro::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	GetStateManager()->GetContext()->m_entityManager->Draw();
	if (m_uiLayer && window)
		m_uiLayer->Draw(*window);
}

void State_GameIntro::Continue(EventDetails* l_details)
{
	
}
