#pragma once

#include <SFML/Graphics.hpp>

#include "../include/Character.h"

enum class ArmorType
{
	None, Light, Medium, Heavy
};

enum class WeaponType
{
	None, Spear, Bow, Shield
};

struct Armor
{
	ArmorType m_type;

	sf::Sprite m_spriteHead;
	sf::Sprite m_spriteTorso;
	sf::Sprite m_spriteShoulders;
	sf::Sprite m_spriteLegs;
	sf::Sprite m_spriteFeet;
};

struct Weapon
{
	WeaponType m_type;
	sf::Sprite m_sprite;

	float m_damage;
};

struct Equiped
{
	Armor m_currentArmor;
	Weapon* m_currentWeapon;
	Weapon* m_currentShield;
	bool m_hasShield;
	bool m_hasBow;
};

class Player : public Character
{
public:
	Player(EntityManager* l_entityManager);
	~Player();

	void Load();

	void UpdateEquiped();
	void DrawEquiped();

	void Update(float l_deltaTime);
	void Draw(sf::RenderWindow* l_window);

	Rectangle GetSpearCollider() { return m_spearCollider; };
	int GetGold();
	int GetArrows();
	void LoadArmor();
	bool GetHasShield() { return m_currentEquiped.m_hasShield; };

	void SetMoveUp(bool l_moving);
	void SetMoveLeft(bool l_moving);
	void SetMoveDown(bool l_moving);
	void SetMoveRight(bool l_moving);
	void SetIsRunning(bool l_isRunning);
	void SetGold(int l_gold);

	void ResetMove();
	void SwitchWeapon();
	void ShootArrow();

	void BuyBow(int l_price);
	void BuyArmor(int l_price);
	void BuyArrow(int l_price);
	void BuyShield(int l_price);
	void BuyPotion(int l_price);

	void TakeDamage(int damage);

private:

	Equiped m_currentEquiped;

	Rectangle m_spearCollider;

	Weapon m_spearWeapon;
	Weapon m_bowWeapon;
	Weapon m_shieldWeapon;

	int m_gold;
	int m_arrows;

	bool m_moveUp;
	bool m_moveDown;
	bool m_moveLeft;
	bool m_moveRight;
	bool m_isRunning;
};