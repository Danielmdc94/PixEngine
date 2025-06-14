#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include "../include/Utilities.h"

struct SharedContext;

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseMoved = sf::Event::MouseMoved,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo 
{
	EventInfo() { m_code = 0; }
	EventInfo(int l_event) { m_code = l_event; }
	union 
	{
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(const std::string& l_bindName) : m_name(l_bindName)
	{
		Clear();
	}
	std::string m_name;
	sf::Vector2f m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2f m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void Clear()
	{
		m_size = sf::Vector2f(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2f(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding
{
	Binding(const std::string& l_name) : m_name(l_name), m_details(l_name), count(0) {}
	void BindEvent(EventType l_type, EventInfo l_info = EventInfo())
	{
		m_events.emplace_back(l_type, l_info);
	}
	Events m_events;
	std::string m_name;
	int count;
	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;

using Callbacks = std::unordered_map<StateType, CallbackContainer>;


class EventManager
{
public:
	EventManager();
	~EventManager();

	void Update();

	void HandleEvent(sf::Event& l_event);
	
	bool AddBinding(Binding* l_binding);
	bool RemoveBinding(std::string l_name);
	
	void SetFocus(const bool& l_focus) { m_hasFocus = l_focus; };
	void SetCurrentState(StateType l_type) { m_currentState = l_type; };
	
	StateType GetCurrentState() { return m_currentState; };
	sf::Vector2i GetMousePosition(sf::RenderWindow* l_wind = nullptr);

	template<typename T>
	bool AddCallback(StateType l_state, const std::string& l_name, void(T::* l_func)(EventDetails*), T* l_instance)
	{
		auto itr = m_callbacks.emplace(l_state, CallbackContainer()).first;
		auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
		return itr->second.emplace(l_name, temp).second;
	}

	bool RemoveCallback(StateType l_state, const std::string& l_name)
	{
		auto itr = m_callbacks.find(l_state);
		if (itr == m_callbacks.end())
			return false;
		auto itr2 = itr->second.find(l_name);
		if (itr2 == itr->second.end())
			return false;
		itr->second.erase(l_name);
		return true;
	}

private:
	void LoadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	StateType m_currentState;
	bool m_hasFocus;
};