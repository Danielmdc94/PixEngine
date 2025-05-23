#include "../include/StateManager.h"

StateManager::StateManager(SharedContext* l_context) : m_context(l_context)
{
	RegisterState<State_EngineIntro>(StateType::EngineIntro);
	RegisterState<State_EngineMenu>(StateType::EngineMenu);
}

StateManager::~StateManager()
{
	for (auto& itr : m_states)
	{
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Update(const sf::Time& l_deltaTime)
{
	if (m_states.empty())
		return;
	if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->IsTranscendent())
					break;
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
			itr->second->Update(l_deltaTime);
	}
	else
		m_states.back().second->Update(l_deltaTime);
}

void StateManager::Draw()
{
	if (m_states.empty())
		return;
	if (m_states.back().second->IsTransparent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->IsTransparent())
					break;
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
		{
			m_context->m_window->GetRenderWindow()->setView(itr->second->GetView());
			itr->second->Draw();
		}
	}
	else
		m_states.back().second->Draw();
}

void StateManager::ProcessRequests()
{
	while (m_toRemove.begin() != m_toRemove.end())
	{
		RemoveState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

bool StateManager::HasState(const StateType& l_type)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if (itr->first == l_type)
		{
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
			if (removed == m_toRemove.end())
				return true;
			return false;
		}
	}
	return false;
}

void StateManager::SwitchTo(const StateType& l_type)
{
	m_context->m_eventManager->SetCurrentState(l_type);
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if (itr->first == l_type)
		{
			m_states.back().second->Deactivate();
			StateType tmp_type = itr->first;
			BaseState* tmp_state = itr->second;
			m_states.erase(itr);
			m_states.emplace_back(tmp_type, tmp_state);
			tmp_state->Activate();
			m_context->m_window->GetRenderWindow()->setView(tmp_state->GetView());
			return;
		}
	}
	if (!m_states.empty())
		m_states.back().second->Deactivate();
	CreateState(l_type);
	m_states.back().second->Activate();
	m_context->m_window->GetRenderWindow()->setView(m_states.back().second->GetView());
}

void StateManager::Remove(const StateType& l_type)
{
	m_toRemove.push_back(l_type);
}

void StateManager::CreateState(const StateType& l_type)
{
	auto newState = m_stateFactory.find(l_type);
	if (newState == m_stateFactory.end())
		return;
	BaseState* state = newState->second();
	state->m_view = m_context->m_window->GetRenderWindow()->getDefaultView();
	m_states.emplace_back(l_type, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& l_type)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if (itr->first == l_type) 
		{
			itr->second->OnDestroy();
			delete itr->second;
			m_states.erase(itr);
			return;
		}
	}
}

SharedContext* StateManager::GetContext()
{
	return m_context;
}

BaseState* StateManager::GetCurrentState()
{
	return m_states.back().second;
}
