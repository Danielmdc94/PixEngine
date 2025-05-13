#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

#include "../include/BaseState.h"
#include "BaseState.h"
#include "State_Intro.h"
#include "SharedContext.h"

enum class StateType
{
	Intro = 1, Menu, Editor
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;


class StateManager
{
public:
	StateManager(SharedContext* l_context);
	~StateManager();

	void Update(const sf::Time& l_deltaTime);
	void Draw();

	void ProcessRequests();

	bool HasState(const StateType& l_type);
	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);

	SharedContext* GetContext();
	BaseState* GetCurrentState();

private:
	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);

	template<class T>
	void RegisterState(const StateType& l_type)
	{
		m_stateFactory[l_type] = [this]() -> BaseState* { return new T(this); };
	}

	SharedContext* m_context;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};

