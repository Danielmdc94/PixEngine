#pragma once

#include <string>

// Entity type ids for this example project. EntityManager itself uses plain
// std::string keys (see include/EntityManager.h), so any project built on
// top of PixEngine can define its own entity type names here.
namespace GameEntityType
{
	inline const std::string Player = "Player";
}
