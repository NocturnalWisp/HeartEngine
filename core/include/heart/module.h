#pragma once

#include <string>

#include <sol/sol.hpp>

namespace HeartEngine
{
#define ADD_LUA_FUNCTION(table, name) table[__STRINGIFY(name)] = &name
#define ADD_LUA_FUNCTION_W_TYPE(table, type, name) table[__STRINGIFY(name)] = &type::name

#define ADD_LUA_COPY(table, name) table[__STRINGIFY(name)] = name

class Engine;

class Module
{
public:
    virtual void registerTypes(Engine& engine, sol::state& lua) {}

    virtual void duringUpdate(Engine& engine) {}
    virtual void closeApplication(Engine& engine) {}

    virtual void startDraw(Engine& engine) {}
    virtual void endDraw(Engine& engine) {}
};
}