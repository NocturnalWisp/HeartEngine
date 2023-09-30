#pragma once

#include <string>

#include <sol/sol.hpp>

#include "component.h"

namespace HeartEngine
{
#define ADD_LUA_FUNCTION(table, name) table[__STRINGIFY(name)] = &name
#define ADD_LUA_FUNCTION_W_TYPE(table, type, name) table[__STRINGIFY(name)] = &type::name

class Engine;

class Module
{
public:
    virtual void registerTypes(Engine& engine, sol::state& lua) {}
};
}