#pragma once

#include <SFML/Graphics.hpp>

class StateManager;
enum class StateType;

class State
{
	friend class StateManager;

public:
	State(StateManager* l_stateManager) : m_stateManager(l_stateManager), m_transparent(false), m_transcendent(false) {};
	virtual ~State() {};

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Update(const sf::Time& l_deltaTime) = 0;
	virtual void Draw() = 0;

	StateManager* GetStateManager() { return m_stateManager; }
	sf::View& GetView() { return m_view; }
	StateType GetType() { return m_type; };


	void SetTransparent(const bool& l_transparent) { m_transparent = l_transparent; };
	bool IsTransparent()const { return m_transparent; }
	void SetTranscendent(const bool& l_transcendence) { m_transcendent = l_transcendence; };
	bool IsTranscendent()const { return m_transcendent; }

protected:
	StateManager* m_stateManager;
	StateType m_type;
	sf::View m_view;
	bool m_transparent;
	bool m_transcendent;
};

