#include "UIButton.h"

UIButton::UIButton()
{
	m_shape.setFillColor(sf::Color(0x53, 0x73, 0x88));
	m_text.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
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
	m_text.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
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

	m_shape.setFillColor(m_isClicked ? sf::Color(0xFF, 0x00, 0x00) : m_isHovered ? sf::Color(0x63, 0x83, 0x98) : sf::Color(0x53, 0x73, 0x88));
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

void UIButton::OnLMouseDown()
{
	if (m_callback && m_isActive && m_isVisible)
	{
		m_isClicked = true;
	}
}

void UIButton::OnLMouseUp()
{
	if (m_callback && m_isActive && m_isVisible && m_isHovered && m_isClicked)
	{
		m_callback();
	}
	m_isClicked = false;
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
