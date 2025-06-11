#pragma once

#include <SFML/Graphics.hpp>
#include "UILayer.h"

class StateManager;
enum class StateType;

class BaseState
{
	friend class StateManager;

public:
	BaseState(StateManager* l_stateManager) : m_stateManager(l_stateManager), m_transparent(false), m_transcendent(false) {}
	virtual ~BaseState() = default;

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Update(const sf::Time& l_deltaTime) = 0;
	virtual void Draw() = 0;

	StateManager* GetStateManager() { return m_stateManager; }
	sf::View& GetView() { return m_view; }
	UILayer* GetUILayer() { return &m_uiLayer; }

	void SetTransparent(const bool& l_transparent) { m_transparent = l_transparent; }
	bool IsTransparent()const { return m_transparent; }
	void SetTranscendent(const bool& l_transcendence) { m_transcendent = l_transcendence; }
	bool IsTranscendent()const { return m_transcendent; }

protected:
	StateManager* m_stateManager;
	sf::View m_view;
	UILayer m_uiLayer;

	bool m_transparent;
	bool m_transcendent;
};

