#include "../include/Player.h"
#include "../include/EntityManager.h"
#include "../include/SharedContext.h"

#include <iostream>

Player::Player(EntityManager* l_entityManager) : Character(l_entityManager), m_spearCollider(sf::Vector2f(0, 0))
{
	Load();
}

Player::~Player()
{

}

void Player::Load()
{
	sf::Rect viewSpace = m_entityManager->GetContext()->m_window->GetViewSpace();
	TextureManager* textureManager = m_entityManager->GetContext()->m_textureManager;
	AudioManager* audioManager = m_entityManager->GetContext()->m_audioManager;

	audioManager->RequireResource("HurtFX");
	audioManager->GetResource("HurtFX")->setVolume(20);

	m_type = EntityType::Player;
	m_name = "Player";
	m_speed = sf::Vector2f(5000.f, 5000.f);
	m_maxVelocity = sf::Vector2f(180.f, 180.f);
	m_friction = sf::Vector2f(0.8f, 0.8f);

	SetSize(64, 64);
	m_textureRect = sf::IntRect(0, m_size.y * 2, m_size.x, m_size.y);

	textureManager->RequireResource("Player");
	textureManager->RequireResource("WeaponSpear");
	textureManager->RequireResource("WeaponShield");
	textureManager->RequireResource("WeaponBow");


	m_sprite.setTexture(*textureManager->GetResource("Player"));
	m_sprite.setTextureRect(m_textureRect);
	m_sprite.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	this->SetPosition(viewSpace.width / 2.0f, viewSpace.height / 2.0f);

	//-----Spear Weapon
	m_spearWeapon.m_type = WeaponType::Spear;
	m_spearWeapon.m_sprite.setTexture(*textureManager->GetResource("WeaponSpear"));
	m_spearWeapon.m_sprite.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_spearWeapon.m_sprite.setRotation(45.f);
	//-----------------

	//-----Bow Weapon
	m_bowWeapon.m_type = WeaponType::Bow;
	m_bowWeapon.m_sprite.setTexture(*textureManager->GetResource("WeaponBow"));
	m_bowWeapon.m_sprite.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_spearWeapon.m_sprite.setRotation(180.f);
	m_bowWeapon.m_sprite.setScale(0.8, 0.8);
	//-----------------

	//-----Shield Weapon
	m_shieldWeapon.m_type = WeaponType::Shield;
	m_shieldWeapon.m_sprite.setTexture(*textureManager->GetResource("WeaponShield"));
	m_shieldWeapon.m_sprite.setTextureRect(m_textureRect);
	m_shieldWeapon.m_sprite.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	//-----------------

	m_currentEquiped.m_currentArmor.m_type = ArmorType::None;
	m_currentEquiped.m_currentWeapon = &m_spearWeapon;
	m_currentEquiped.m_currentShield = &m_shieldWeapon;
	m_currentEquiped.m_hasShield = false;
	m_currentEquiped.m_hasBow = false;
	LoadArmor();

	m_gold = 0;
	m_maxHitPoints = 100;
	m_hitPoints = m_maxHitPoints;
	m_arrows = 0;

	m_moveDown = false;
	m_moveLeft = false;
	m_moveRight = false;
	m_moveUp = false;
	m_isRunning = false;
}

void Player::UpdateEquiped()
{
	sf::RenderWindow* window = m_entityManager->GetContext()->m_window->GetRenderWindow();

	m_currentEquiped.m_currentArmor.m_spriteHead.setPosition(m_position);
	m_currentEquiped.m_currentArmor.m_spriteTorso.setPosition(m_position);
	m_currentEquiped.m_currentArmor.m_spriteShoulders.setPosition(m_position);
	m_currentEquiped.m_currentArmor.m_spriteLegs.setPosition(m_position);
	m_currentEquiped.m_currentArmor.m_spriteFeet.setPosition(m_position);

	m_currentEquiped.m_currentShield->m_sprite.setPosition(m_position);

	m_currentEquiped.m_currentWeapon->m_sprite.setPosition(m_position);
	sf::Vector2i mousePosition = m_entityManager->GetContext()->m_eventManager->GetMousePosition();
	sf::Vector2f spritePosition = m_currentEquiped.m_currentWeapon->m_sprite.getPosition();
	sf::Vector2f direction = (sf::Vector2f)mousePosition - spritePosition;

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f normalizedDirection = direction / magnitude;

	if (m_currentEquiped.m_currentWeapon->m_type == WeaponType::Spear && !m_isRunning)
	{
		float offsetDistance = 20.0f;
		sf::Vector2f offsetPosition = (spritePosition + normalizedDirection * offsetDistance) + sf::Vector2f(0, 5);
		m_currentEquiped.m_currentWeapon->m_sprite.setPosition(offsetPosition);

		float spearheadDistance = 32.0f;
		sf::Vector2f spearHeadPosition = offsetPosition + normalizedDirection * spearheadDistance;

		float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
		m_currentEquiped.m_currentWeapon->m_sprite.setRotation(angle + 135);

		m_spearCollider = Rectangle(sf::Vector2f(24, 24), spearHeadPosition);
	}
	else
		m_spearCollider = Rectangle(sf::Vector2f(0, 0), sf::Vector2f(0, 0));

	if (m_currentEquiped.m_currentWeapon->m_type == WeaponType::Bow)
	{
		float offsetDistance = 30.0f;
		sf::Vector2f offsetPosition = spritePosition + normalizedDirection * offsetDistance;
		m_currentEquiped.m_currentWeapon->m_sprite.setPosition(offsetPosition);
		float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
		m_currentEquiped.m_currentWeapon->m_sprite.setRotation(angle);
	}
}

void Player::DrawEquiped()
{
	sf::RenderWindow* window = m_entityManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_currentEquiped.m_currentArmor.m_spriteHead);
	window->draw(m_currentEquiped.m_currentArmor.m_spriteTorso);
	window->draw(m_currentEquiped.m_currentArmor.m_spriteShoulders);
	window->draw(m_currentEquiped.m_currentArmor.m_spriteLegs);
	window->draw(m_currentEquiped.m_currentArmor.m_spriteFeet);

	if (m_currentEquiped.m_hasShield && m_currentEquiped.m_currentWeapon->m_type != WeaponType::Bow)
		window->draw(m_currentEquiped.m_currentShield->m_sprite);
	if (!m_isRunning)
		window->draw(m_currentEquiped.m_currentWeapon->m_sprite);
}

void Player::Update(float l_deltaTime)
{
	if (m_isRunning)
		m_maxVelocity = sf::Vector2f(400.f, 400.f);
	else
		m_maxVelocity = sf::Vector2f(180.f, 180.f);
	if (m_moveDown)
		MoveInDirection(Direction::Down);
	if (m_moveLeft)
		MoveInDirection(Direction::Left);
	if (m_moveRight)
		MoveInDirection(Direction::Right);
	if (m_moveUp)
		MoveInDirection(Direction::Up);
	
	Character::Update(l_deltaTime);
	UpdateEquiped();
}

void Player::Draw(sf::RenderWindow* l_window)
{
	if (m_isHurt)
	{
		FlashSprite(&m_currentEquiped.m_currentArmor.m_spriteFeet, sf::Color::Red, nullptr);
		FlashSprite(&m_currentEquiped.m_currentArmor.m_spriteLegs, sf::Color::Red, nullptr);
		FlashSprite(&m_currentEquiped.m_currentArmor.m_spriteTorso, sf::Color::Red, nullptr);
		FlashSprite(&m_currentEquiped.m_currentArmor.m_spriteShoulders, sf::Color::Red, nullptr);
		FlashSprite(&m_currentEquiped.m_currentArmor.m_spriteHead, sf::Color::Red, nullptr);
	}
	Character::Draw(l_window);
	DrawEquiped();
}

void Player::SetMoveUp(bool l_moving)
{
	m_moveUp = l_moving;
}

void Player::SetMoveLeft(bool l_moving)
{
	m_moveLeft = l_moving;
}

void Player::SetMoveDown(bool l_moving)
{
	m_moveDown = l_moving;
}

void Player::SetMoveRight(bool l_moving)
{
	m_moveRight = l_moving;
}

void Player::SetIsRunning(bool l_running)
{
	m_isRunning = l_running;
}

void Player::ResetMove()
{
	m_moveUp = false;
	m_moveDown = false;
	m_moveLeft = false;
	m_moveRight = false;
	m_isRunning = false;
}

void Player::SwitchWeapon()
{
	if (m_currentEquiped.m_currentWeapon->m_type == WeaponType::Bow)
		m_currentEquiped.m_currentWeapon = &m_spearWeapon;
	else if (m_currentEquiped.m_currentWeapon->m_type == WeaponType::Spear && m_currentEquiped.m_hasBow)
		m_currentEquiped.m_currentWeapon = &m_bowWeapon;
	else
		return;
}

void Player::ShootArrow()
{
	if (!m_isRunning && m_currentEquiped.m_currentWeapon->m_type ==WeaponType::Bow &&  m_arrows > 0)
	{
		m_arrows -= 1;
		m_entityManager->CreateEntity(EntityType::Arrow);
	}
}

void Player::BuyBow(int l_price)
{
	if (l_price <= m_gold)
	{
		if (!m_currentEquiped.m_hasBow)
		{
			m_currentEquiped.m_hasBow = true;
			m_currentEquiped.m_currentWeapon = &m_bowWeapon;
			m_gold -= l_price;
		}
	}
}

void Player::BuyArmor(int l_price)
{
	if (l_price <= m_gold)
	{
		if (m_currentEquiped.m_currentArmor.m_type == ArmorType::None)
			m_currentEquiped.m_currentArmor.m_type = ArmorType::Light;

		else if (m_currentEquiped.m_currentArmor.m_type == ArmorType::Light)
			m_currentEquiped.m_currentArmor.m_type = ArmorType::Medium;

		else if (m_currentEquiped.m_currentArmor.m_type == ArmorType::Medium)
			m_currentEquiped.m_currentArmor.m_type = ArmorType::Heavy;

		else
			return;

		LoadArmor();
		SetGold(m_gold - l_price);;
		SetMaxHitpoints(m_maxHitPoints + 20 * int(m_currentEquiped.m_currentArmor.m_type));
	}
}

void Player::BuyArrow(int l_price)
{
	if (l_price <= m_gold && m_arrows < 30)
	{
		SetGold(m_gold - l_price);
		m_arrows += 10;
		if (m_arrows > 30)
			m_arrows = 30;
	}
}

void Player::BuyShield(int l_price)
{
	if (l_price <= m_gold)
	{
		if (!m_currentEquiped.m_hasShield)
		{
			SetGold(m_gold - l_price);;
			m_currentEquiped.m_hasShield = true;
		}
	}
}

void Player::BuyPotion(int l_price)
{
	if (l_price <= m_gold)
	{
		if (m_hitPoints < m_maxHitPoints)
		{
			SetGold(m_gold - l_price);
			SetHitpoints(m_hitPoints + 25);
		}
	}
}

void Player::TakeDamage(int l_damage)
{
	if (GetHasShield())
		l_damage = int(l_damage * 0.5f);
	if (!Character::TakeDamage(l_damage))
		return;
	AudioManager* audioManager = m_entityManager->GetContext()->m_audioManager;

	audioManager->GetResource("HurtFX")->play();
}

void Player::SetGold(int l_gold)
{
	if (l_gold < 0)
		l_gold = 0;
	else if (l_gold > 9999)
		l_gold = 9999;
		m_gold = l_gold;
}

int Player::GetGold()
{
	return m_gold;
}

int Player::GetArrows()
{
	return m_arrows;
}


void Player::LoadArmor()
{

	TextureManager* textureManager = m_entityManager->GetContext()->m_textureManager;

	switch (m_currentEquiped.m_currentArmor.m_type)
	{
	case ArmorType::None:
		textureManager->RequireResource("HeadNone");
		textureManager->RequireResource("TorsoLight");
		textureManager->RequireResource("LegsLight");
		textureManager->RequireResource("FeetLight");
		m_currentEquiped.m_currentArmor.m_spriteHead.setTexture(*textureManager->GetResource("HeadNone"));
		m_currentEquiped.m_currentArmor.m_spriteTorso.setTexture(*textureManager->GetResource("TorsoLight"));
		m_currentEquiped.m_currentArmor.m_spriteLegs.setTexture(*textureManager->GetResource("LegsLight"));
		m_currentEquiped.m_currentArmor.m_spriteFeet.setTexture(*textureManager->GetResource("FeetLight"));
		break;
	case ArmorType::Light:
		textureManager->RequireResource("HeadLight");
		textureManager->RequireResource("ShouldersLight");
		textureManager->RequireResource("TorsoLight");
		textureManager->RequireResource("LegsLight");
		textureManager->RequireResource("FeetLight");
		m_currentEquiped.m_currentArmor.m_spriteHead.setTexture(*textureManager->GetResource("HeadLight"));
		m_currentEquiped.m_currentArmor.m_spriteShoulders.setTexture(*textureManager->GetResource("ShouldersLight"));
		m_currentEquiped.m_currentArmor.m_spriteTorso.setTexture(*textureManager->GetResource("TorsoLight"));
		m_currentEquiped.m_currentArmor.m_spriteLegs.setTexture(*textureManager->GetResource("LegsLight"));
		m_currentEquiped.m_currentArmor.m_spriteFeet.setTexture(*textureManager->GetResource("FeetLight"));
		break;
	case ArmorType::Medium:
		textureManager->RequireResource("HeadMedium");
		textureManager->RequireResource("ShouldersLight");
		textureManager->RequireResource("TorsoMedium");
		textureManager->RequireResource("LegsLight");
		textureManager->RequireResource("FeetHeavy");
		m_currentEquiped.m_currentArmor.m_spriteHead.setTexture(*textureManager->GetResource("HeadMedium"));
		m_currentEquiped.m_currentArmor.m_spriteShoulders.setTexture(*textureManager->GetResource("ShouldersLight"));
		m_currentEquiped.m_currentArmor.m_spriteTorso.setTexture(*textureManager->GetResource("TorsoMedium"));
		m_currentEquiped.m_currentArmor.m_spriteLegs.setTexture(*textureManager->GetResource("LegsLight"));
		m_currentEquiped.m_currentArmor.m_spriteFeet.setTexture(*textureManager->GetResource("FeetHeavy"));
		break;
	case ArmorType::Heavy:
		textureManager->RequireResource("HeadHeavy");
		textureManager->RequireResource("ShouldersHeavy");
		textureManager->RequireResource("TorsoHeavy");
		textureManager->RequireResource("LegsHeavy");
		textureManager->RequireResource("FeetHeavy");
		m_currentEquiped.m_currentArmor.m_spriteHead.setTexture(*textureManager->GetResource("HeadHeavy"));
		m_currentEquiped.m_currentArmor.m_spriteShoulders.setTexture(*textureManager->GetResource("ShouldersHeavy"));
		m_currentEquiped.m_currentArmor.m_spriteTorso.setTexture(*textureManager->GetResource("TorsoHeavy"));
		m_currentEquiped.m_currentArmor.m_spriteLegs.setTexture(*textureManager->GetResource("LegsHeavy"));
		m_currentEquiped.m_currentArmor.m_spriteFeet.setTexture(*textureManager->GetResource("FeetHeavy"));
		break;

	default:
		return;
	}
	m_currentEquiped.m_currentArmor.m_spriteHead.setTextureRect(m_textureRect);
	m_currentEquiped.m_currentArmor.m_spriteHead.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_currentEquiped.m_currentArmor.m_spriteShoulders.setTextureRect(m_textureRect);
	m_currentEquiped.m_currentArmor.m_spriteShoulders.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_currentEquiped.m_currentArmor.m_spriteTorso.setTextureRect(m_textureRect);
	m_currentEquiped.m_currentArmor.m_spriteTorso.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_currentEquiped.m_currentArmor.m_spriteLegs.setTextureRect(m_textureRect);
	m_currentEquiped.m_currentArmor.m_spriteLegs.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
	m_currentEquiped.m_currentArmor.m_spriteFeet.setTextureRect(m_textureRect);
	m_currentEquiped.m_currentArmor.m_spriteFeet.setOrigin(m_textureRect.width / 2.0f, m_textureRect.height / 2.0f);
}
