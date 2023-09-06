#pragma once

#include <sol.hpp>
#include <string>

#include "node.h"
#include "engine.h"

void lw_getNodeWrapper(sol::state& lua, Node& node);
