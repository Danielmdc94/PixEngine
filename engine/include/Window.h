#pragma once

#include <SFML/Graphics.hpp>
#include "../include/EventManager.h"

class Window
{
public:
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw();
	void Draw(sf::Drawable& l_drawable);
	void EndDraw();
	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool IsFocused() { return m_isFocused; };

	EventManager* GetEventManager() { return &m_eventManager; };
	sf::RenderWindow* GetRenderWindow() { return &m_window; };
	sf::Vector2u GetWindowSize();
	sf::FloatRect GetViewSpace();

	void SetIsDone(const bool l_isDone);
	void SetFocus(const bool& l_focus) { m_isFocused = l_focus; };

	void ToggleFullscreen(EventDetails* l_details);
	void Close(EventDetails* l_details);

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	EventManager m_eventManager;
	
	bool m_isDone;
	bool m_isFullscreen;
	bool m_isFocused;
};
