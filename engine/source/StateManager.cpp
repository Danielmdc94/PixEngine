#include "../include/StateManager.h"
#include "../include/SharedContext.h"
#include <iostream>

StateManager::StateManager(SharedContext* l_context) : m_context(l_context)
{

}

StateManager::~StateManager()
{

}

void StateManager::Update(const sf::Time& l_deltaTime)
{
	if (m_states.empty())
		return;
	if (m_states.back()->IsTranscendent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!(*itr)->IsTranscendent())
					break;
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
			(*itr)->Update(l_deltaTime);
	}
	else
		m_states.back()->Update(l_deltaTime);
}

void StateManager::Draw()
{
	if (m_states.empty())
		return;
	if (m_states.back()->IsTransparent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!(*itr)->IsTransparent())
					break;
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
		{
			m_context->m_window->GetRenderWindow()->setView((*itr)->GetView());
			(*itr)->Draw();
		}
	}
	else
		m_states.back()->Draw();
}

void StateManager::SwitchTo(const StateType& l_type)
{
	m_context->m_eventManager->SetCurrentState(l_type);
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if ((*itr)->m_type == l_type)
		{
			if (itr == m_states.end() - 1)
				return;
			auto newState = std::move(*itr);
			m_states.erase(itr);
			m_states.push_back(std::move(newState));
			if (!m_states.empty())
				m_states[m_states.size() - 2]->Deactivate();
			m_states.back()->Activate();
			m_context->m_window->GetRenderWindow()->setView(m_states.back()->GetView());
			return;
		}
	}
	if (!m_states.empty())
		m_states.back()->Deactivate();
	CreateState(l_type);
	m_states.back()->Activate();
	m_context->m_window->GetRenderWindow()->setView(m_states.back()->GetView());
}

void StateManager::CreateState(const StateType& l_type)
{
	std::unique_ptr<State> newState = nullptr;
	if (l_type == StateType::Intro)
		newState = std::make_unique<State_Intro>(this);
	else
		return;
	
	newState->OnCreate();
	newState->m_view = m_context->m_window->GetRenderWindow()->getDefaultView();
	newState->Activate();
	m_states.push_back(std::move(newState));
}

void StateManager::Remove(const StateType& l_type)
{
	if (m_states.empty())
		return;

	bool wasTopState = false;
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if ((*itr)->GetType() == l_type)
		{
			wasTopState = (itr == m_states.end() - 1);
			(*itr)->OnDestroy();
			m_states.erase(itr);
			break;
		}
	}

	if (wasTopState && !m_states.empty())
	{
		m_states.back()->Activate();
		m_context->m_window->GetRenderWindow()->setView(m_states.back()->GetView());
	}
}

SharedContext* StateManager::GetContext()
{
	return m_context;
}

State* StateManager::GetCurrentState()
{
	return m_states.back().get();
}
