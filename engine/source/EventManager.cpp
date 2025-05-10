#pragma once

#include "../include/StateManager.h"
#include "../include/EventManager.h"
#include "../include/SharedContext.h"

EventManager::EventManager(SharedContext* context) : m_context(context)
{

}

EventManager::~EventManager()
{

}

sf::Vector2i EventManager::GetMousePosition()
{
	return m_mousePosition;
}

void EventManager::Update()
{
	sf::Event event;
	Window* window = m_context->m_window;

	m_mousePosition = sf::Mouse::getPosition(*window->GetRenderWindow());

	while (window->GetRenderWindow()->pollEvent(event))
	{
		HandleGeneralEvents(event);

		switch (m_currentState)
		{
			case StateType::Intro:
				HandleIntroEvents(event);
				break;

			case StateType::Game:
				HandleGameEvents(event);
				break;

			case StateType::Paused:
				HandlePausedEvents(event);
				break;

			case StateType::Store:
				HandleStoreEvents(event);
				break;

			case StateType::GameOver:
				HandleGameOverEvents(event);
				break;
			default:
				break;
		}
	}
}

void EventManager::HandleGeneralEvents(sf::Event l_event)
{
	Window* window = m_context->m_window;

	switch (l_event.type)
	{
	case sf::Event::Closed:
		window->SetIsDone(true);
		break;

	case sf::Event::LostFocus:
		window->SetFocus(false);
		break;

	case sf::Event::GainedFocus:
		window->SetFocus(true);
		break;

	case sf::Event::KeyPressed:
		if (l_event.key.code == sf::Keyboard::F4)
			window->ToggleFullscreen();
		break;

	default:
		break;
	}
}

void EventManager::HandleGameEvents(sf::Event l_event)
{
	Window* window = m_context->m_window;
	State_Game* currentStatePtr = dynamic_cast<State_Game*>(m_context->m_stateManager->GetCurrentState());
	Player* player = m_context->m_entityManager->GetPlayer();

	switch (l_event.type)
	{
	case sf::Event::KeyPressed:
		if (l_event.key.code == sf::Keyboard::Escape)
			currentStatePtr->Pause();
		if (l_event.key.code == sf::Keyboard::Tab)
			currentStatePtr->Store();
		if (l_event.key.code == sf::Keyboard::W)
			player->SetMoveUp(true);
		if (l_event.key.code == sf::Keyboard::A)
			player->SetMoveLeft(true);
		if (l_event.key.code == sf::Keyboard::S)
			player->SetMoveDown(true);
		if (l_event.key.code == sf::Keyboard::D)
			player->SetMoveRight(true);
		if (l_event.key.code == sf::Keyboard::LShift)
			player->SetIsRunning(true);
		if (l_event.key.code == sf::Keyboard::E)
			player->SwitchWeapon();
		if (l_event.key.code == sf::Keyboard::O)
			player->SetGold(player->GetGold() + 10);
		break;

	case sf::Event::KeyReleased:
		if (l_event.key.code == sf::Keyboard::W)
			player->SetMoveUp(false);
		if (l_event.key.code == sf::Keyboard::A)
			player->SetMoveLeft(false);
		if (l_event.key.code == sf::Keyboard::S)
			player->SetMoveDown(false);
		if (l_event.key.code == sf::Keyboard::D)
			player->SetMoveRight(false);
		if (l_event.key.code == sf::Keyboard::LShift)
			player->SetIsRunning(false);
		break;

	case sf::Event::MouseButtonPressed:
		if (l_event.mouseButton.button == sf::Mouse::Left)
			player->ShootArrow();
		break;

	default:
		break;
	}
}

void EventManager::HandlePausedEvents(sf::Event l_event)
{
	Window* window = m_context->m_window;
	State_Paused* currentStatePtr = dynamic_cast<State_Paused*>(m_context->m_stateManager->GetCurrentState());

	switch (l_event.type)
	{
	case sf::Event::KeyPressed:
		if (l_event.key.code == sf::Keyboard::F4)
			break;
		else
			currentStatePtr->Unpause();
		break;

	default:
		break;
	}
}

void EventManager::HandleGameOverEvents(sf::Event l_event)
{
	Window* window = m_context->m_window;
	State_GameOver* currentStatePtr = dynamic_cast<State_GameOver*>(m_context->m_stateManager->GetCurrentState());

	switch (l_event.type)
	{
	case sf::Event::KeyPressed:
		if (l_event.key.code == sf::Keyboard::Space)
			currentStatePtr->Restart();
		break;

	default:
		break;
	}
}


void EventManager::HandleIntroEvents(sf::Event l_event)
{
	Window* window = m_context->m_window;
	State_Intro* currentStatePtr = dynamic_cast<State_Intro*>(m_context->m_stateManager->GetCurrentState());

	switch (l_event.type)
	{
	case sf::Event::KeyPressed:
		if (l_event.key.code == sf::Keyboard::F4)
			break;
		else
			currentStatePtr->Continue();
		break;

	default:
		break;
	}
}

void EventManager::HandleStoreEvents(sf::Event l_event)
{
	Window* window = m_context->m_window;
	State_Store* currentStatePtr = dynamic_cast<State_Store*>(m_context->m_stateManager->GetCurrentState());

	switch (l_event.type)
	{
	case sf::Event::KeyPressed:
		if (l_event.key.code == sf::Keyboard::F4)
			break;
		if (l_event.key.code == sf::Keyboard::Tab)
			currentStatePtr->Close();
		break;

	case sf::Event::MouseButtonPressed:
		if (l_event.mouseButton.button == sf::Mouse::Left)
			currentStatePtr->BuyItem(GetMousePosition());
		break;

	default:
		break;
	}
}

