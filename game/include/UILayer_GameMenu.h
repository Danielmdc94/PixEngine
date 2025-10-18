#pragma once

#include "UILayer.h"
#include "UIButton.h"

class UILayer_GameMenu : public UILayer
{
public:
	explicit UILayer_GameMenu(BaseState* l_owner) : UILayer(l_owner) {}
	virtual ~UILayer_GameMenu() = default;

	void OnCreate() override;
	void PlayButton();
	void QuitButton();
};
