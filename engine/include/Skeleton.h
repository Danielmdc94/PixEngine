#pragma once

#include "../include/Character.h"

class Skeleton : public Character
{
public:
    Skeleton(EntityManager* l_entityManager);
    ~Skeleton();

    void Load();

    void Update(float l_deltaTime);
    void Draw(sf::RenderWindow* l_window);

    void TakeDamage(int l_damage);

    void SetIsKilled(bool l_isKilled) { m_isKilled = l_isKilled; }
    bool IsKilled() { return m_isKilled; }

private:
    bool m_isKilled = false;
};