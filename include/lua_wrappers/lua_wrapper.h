#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <map>

#include <sol.hpp>

#include "lua_node.h"
#include "lw_node.h"
#include "lw_engine_texture_rect.h"

// #include "lw_node.h"
// #include "lw_engine_texture_rect.h"

// Mapping wrappers, can be added to.
std::map<std::string, void(*)(sol::state&, Node&)> wrappers
{
    {"Node", lw_getNodeWrapper},
    {"TextureRect", lw_getEngineTextureRectWrapper}
};