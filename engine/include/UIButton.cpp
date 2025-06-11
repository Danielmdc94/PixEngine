#include "UIButton.h"

UIButton::UIButton() : m_isHovered(false)
{
	m_shape.setFillColor(sf::Color::White);
	m_text.setFillColor(sf::Color::Black);
}

void UIButton::SetSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
}

void UIButton::SetText(const std::string& text, const sf::Font& font)
{
	m_text.setFont(font);
	m_text.setString(text);
	CenterText();
}

void UIButton::SetCallback(Callback callback)
{
	m_callback = callback;
}

void UIButton::Update(const sf::Time& deltaTime)
{
	if (!m_isActive)
	{
		return;
	}

	m_shape.setFillColor(m_isHovered ? sf::Color(200, 200, 200) : sf::Color::White);
}

void UIButton::Draw(sf::RenderTarget& target)
{
	if (!m_isVisible)
	{
		return;
	}

	m_shape.setPosition(m_position);
	target.draw(m_shape);
	target.draw(m_text);
}

bool UIButton::Contains(const sf::Vector2f& point) const
{
	return m_shape.getGlobalBounds().contains(point);
}

void UIButton::OnHover(bool isHovered)
{
	m_isHovered = isHovered;
}

void UIButton::OnClick()
{
	if (m_callback && m_isActive && m_isVisible)
	{
		m_callback();
	}
}

void UIButton::CenterText()
{
	sf::FloatRect textBounds = m_text.getLocalBounds();
	sf::FloatRect shapeBounds = m_shape.getLocalBounds();

	m_text.setPosition(
		m_position.x + (shapeBounds.width - textBounds.width) / 2.f,
		m_position.y + (shapeBounds.height - textBounds.height) / 2.f
	);
}
