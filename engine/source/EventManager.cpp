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
