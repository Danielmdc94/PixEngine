#pragma once

#include <cstdint>

// StateType is a generic, host-extensible identifier for engine/game states.
// The engine only reserves the values below; any project built on top of
// PixEngine should define its own state ids starting at UserStateStart
// (see example/include/GameStateType.h for a sample) instead of modifying
// this header.
using StateType = std::uint32_t;

namespace EngineStateType
{
	constexpr StateType EngineIntro = 1;

	// Host/game projects must define their own StateType values starting
	// from this offset to avoid colliding with engine-reserved ids.
	constexpr StateType UserStateStart = 100;
}
