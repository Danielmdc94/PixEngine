#pragma once

#include "UILayer.h"
#include "UIButton.h"

class UILayer_EngineMenu : public UILayer
{
public:
	explicit UILayer_EngineMenu(BaseState* l_owner) : UILayer(l_owner) {}
	virtual ~UILayer_EngineMenu() = default;

	void OnCreate() override;
	void PlayButton();
	void QuitButton();
};
