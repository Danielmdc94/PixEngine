#pragma once

#include "SharedContext.h"

class UIManager
{
public:
    UIManager(SharedContext* context);
    ~UIManager();
    
    void Update(const sf::Time& l_deltaTime);
    void Draw();
    
private:
    SharedContext* m_context;
};
