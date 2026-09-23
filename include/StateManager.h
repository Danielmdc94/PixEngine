#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

#include "SharedContext.h"
#include "BaseState.h"
#include "StateType.h"
#include "State_EngineIntro.h"

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

	// Lets host/game code plug in its own states without the engine core
	// knowing about them.
	template<typename T>
	void RegisterState(const StateType& l_type)
	{
		m_stateFactory[l_type] = [this]() -> BaseState* { return new T(this); };
	}

	// The state the engine switches to once the built-in intro finishes.
	// Host code must set this (e.g. to its own main menu state) before
	// running the engine loop.
	void SetInitialState(const StateType& l_type) { m_initialState = l_type; }
	StateType GetInitialState() const { return m_initialState; }

	SharedContext* GetContext();
	BaseState* GetCurrentState();

private:
	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);

	SharedContext* m_context;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
	StateType m_initialState = 0;
};

