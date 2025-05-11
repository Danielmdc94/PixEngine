#pragma once

#include <memory>

#include "State.h"
#include "State_Intro.h"
#include "SharedContext.h"

enum class StateType
{
	Intro = 1, Game, Paused, Store, GameOver
};

class StateManager
{
public:
	StateManager(SharedContext* l_context);
	~StateManager();

	void Update(const sf::Time& l_deltaTime);
	void Draw();

	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);

	SharedContext* GetContext();
	State* GetCurrentState();

private:
	void CreateState(const StateType& l_type);

	SharedContext* m_context;

	std::vector<std::unique_ptr<State>> m_states;
};

