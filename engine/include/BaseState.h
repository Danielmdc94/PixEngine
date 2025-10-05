#pragma once

#include <SFML/Graphics.hpp>
#include "UILayer.h"
#include "EventManager.h"

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
	UILayer* GetUILayer() { return m_uiLayer.get(); }

	template<typename T = UILayer>
	void CreateUILayer() {
		static_assert(std::is_base_of<UILayer, T>::value, "T must inherit from UILayer");
		m_uiLayer = std::make_unique<T>(this);
		m_uiLayer->OnCreate();
	}

	template<typename T = UILayer>
	T* GetUILayer() const {
		static_assert(std::is_base_of<UILayer, T>::value, "T must inherit from UILayer");
		return static_cast<T*>(m_uiLayer.get());
	}

	UILayer* GetUILayerRaw() const { return m_uiLayer.get(); }
	bool HasUILayer() const { return m_uiLayer != nullptr; }

	void ClearUILayer() {
		if (m_uiLayer) {
			m_uiLayer->OnDestroy();
			m_uiLayer.reset();
		}
	}
	
	void SetTransparent(const bool& l_transparent) { m_transparent = l_transparent; }
	bool IsTransparent()const { return m_transparent; }
	void SetTranscendent(const bool& l_transcendence) { m_transcendent = l_transcendence; }
	bool IsTranscendent()const { return m_transcendent; }

protected:
	StateManager* m_stateManager;
	sf::View m_view;
	
	std::unique_ptr<UILayer> m_uiLayer;

	bool m_transparent;
	bool m_transcendent;
};

