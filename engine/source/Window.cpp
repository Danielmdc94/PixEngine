#include "../include/Window.h"

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	Setup(l_title, l_size);
}

Window::~Window()
{
	Destroy();
}

void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	m_isFocused = true;
	Create();
}

void Window::Create()
{
	sf::Uint32 style;
	if (m_isFullscreen)
		style = sf::Style::Fullscreen;
	else
		style = sf::Style::Titlebar | sf::Style::Close;
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	m_window.setKeyRepeatEnabled(false);
	m_window.setFramerateLimit(60);
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Update()
{
	
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_window.display();
}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

void Window::Draw(sf::Drawable& l_drawable)
{
	m_window.draw(l_drawable);
}

sf::FloatRect Window::GetViewSpace()
{
	sf::Vector2f viewCenter = m_window.getView().getCenter();
	sf::Vector2f viewSize = m_window.getView().getSize();
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}

void Window::SetIsDone(const bool l_isDone)
{
	m_isDone = l_isDone;
}