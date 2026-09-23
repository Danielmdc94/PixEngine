#pragma once

#include "StateType.h"

// Example-project state ids. Any project built on top of PixEngine defines
// its own set of these, starting at EngineStateType::UserStateStart so they
// never collide with engine-reserved ids (see include/StateType.h).
namespace GameStateType
{
	constexpr StateType GameIntro = EngineStateType::UserStateStart + 1;
	constexpr StateType GameMenu  = EngineStateType::UserStateStart + 2;
	constexpr StateType Game      = EngineStateType::UserStateStart + 3;
	constexpr StateType Pause     = EngineStateType::UserStateStart + 4;
}
