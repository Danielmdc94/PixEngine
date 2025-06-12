#pragma once

#include <iostream>

#include "UILayer.h"
#include "UIButton.h"

class UILayer_EngineMenu : public UILayer
{
public:
	UILayer_EngineMenu() = default;
	virtual ~UILayer_EngineMenu() = default;

	void SetupButtons(const sf::Font& font);
};
