#include "../include/Arrow.h"
#include "../include/EntityManager.h"
#include "../include/SharedContext.h"

Arrow::Arrow(EntityManager* l_entityManager) : Entity(l_entityManager)
{
	Load();
}

Arrow::~Arrow()
{

}

void Arrow::Load()
{
	m_position = m_entityManager->GetPlayer()->GetPosition();
	TextureManager* textureManager = m_entityManager->GetContext()->m_textureManager;

	textureManager->RequireResource("WeaponArrow");
	m_sprite.setTexture(*textureManager->GetResource("WeaponArrow"));
	m_sprite.setOrigin(textureManager->GetResource("WeaponArrow")->getSize().x / 2.0f, textureManager->GetResource("WeaponArrow")->getSize().y / 2.0f);
	m_sprite.setScale(0.5, 0.5);
	m_sprite.setPosition(m_position);

	m_type = EntityType::Arrow;
	m_name = "Arrow";
	m_speed = sf::Vector2f(5000.f, 5000.f);
	m_maxVelocity = sf::Vector2f(600.f, 600.f);
	m_friction = sf::Vector2f(0.5f, 0.5f);
	m_size = sf::Vector2f(textureManager->GetResource("WeaponArrow")->getSize().x * 0.5, textureManager->GetResource("WeaponArrow")->getSize().x * 0.5);
	m_boxCollider = Rectangle(GetSize(), GetPosition());
	m_state = EntityState::Moving;

	sf::Vector2f targetPosition = sf::Vector2f(m_entityManager->GetContext()->m_eventManager->GetMousePosition());
    m_direction = targetPosition - m_position;

	float magnitude = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	if (magnitude != 0.0f)
		m_direction /= magnitude;

	float angle = std::atan2(m_direction.y, m_direction.x) * 180.0f / 3.14159265f;
	m_sprite.setRotation(angle);
}

void Arrow::Update(float l_deltaTime)
{
	float speed = 350.0f;
	m_position += m_direction * speed * l_deltaTime;
	m_sprite.setPosition(m_position);

	sf::Vector2f windowSize = sf::Vector2f(m_entityManager->GetContext()->m_window->GetRenderWindow()->getSize());
	if (m_position.x < 0 || m_position.y < 0 || m_position.x > windowSize.x || m_position.y > windowSize.y)
		m_isMarkedForDeletion = true;
	m_boxCollider = Rectangle(GetSize(), GetPosition());
}

void Arrow::Draw(sf::RenderWindow* l_wind)
{
	sf::RenderWindow* window = m_entityManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_sprite);
}

