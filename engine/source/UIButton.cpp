#include "UIButton.h"

UIButton::UIButton() : m_isHovered(false)
{
	m_shape.setFillColor(sf::Color::White);
	m_text.setFillColor(sf::Color::Black);
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
	CenterText();
}

void UIButton::SetCallback(Callback callback)
{
	m_callback = callback;
}

void UIButton::Update(const sf::Time& l_deltaTime)
{
	if (!m_isActive)
	{
		return;
	}

	m_shape.setFillColor(m_isHovered ? sf::Color(200, 200, 200) : sf::Color::Blue);
}

void UIButton::Draw(sf::RenderTarget& l_target)
{
	if (!m_isVisible)
	{
		return;
	}

	m_shape.setPosition(m_position);
	l_target.draw(m_shape);
	l_target.draw(m_text);
}

bool UIButton::Contains(const sf::Vector2f& l_point) const
{
	return m_shape.getGlobalBounds().contains(l_point);
}

void UIButton::OnHover(bool l_isHovered)
{
	m_isHovered = l_isHovered;
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
		m_position.x + (shapeBounds.width / 2.f) - (textBounds.width / 2.f) - textBounds.left,
		m_position.y + (shapeBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top
	);
}
