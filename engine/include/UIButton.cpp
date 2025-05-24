#include "UIButton.h"

void UIButton::OnCreate()
{
	m_shape.setSize({100.f, 40.f});
	m_shape.setFillColor(sf::Color::Blue);
	m_shape.setPosition(m_position);
	m_text.setFillColor(sf::Color::White);
}

void UIButton::OnDestroy()
{
	
}

void UIButton::Update(const sf::Time& l_deltaTime)
{
	m_shape.setPosition(m_position);
	m_text.setPosition(m_position + sf::Vector2f(10.f, 5.f));
}

void UIButton::Draw()
{
	sf::RenderWindow* window = m_uiManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_shape);
	window->draw(m_text);
}

void UIButton::SetSize(const sf::Vector2f& l_size)
{
	m_shape.setSize(l_size);
}

void UIButton::SetText(const std::string& l_text, const sf::Font& l_font, unsigned int l_charSize)
{
	m_text.setFont(l_font);
	m_text.setString(l_text);
	m_text.setCharacterSize(l_charSize);
	m_text.setFillColor(sf::Color::White);
}

void UIButton::SetCallback(std::function<void()> l_callback)
{
	m_callback = l_callback;
}

void UIButton::OnClick()
{
	if (m_callback)
	{
		m_callback();
	}
}

bool UIButton::IsHovered(const sf::Vector2f& mousePos) const
{
	return m_shape.getGlobalBounds().contains(mousePos);
}
