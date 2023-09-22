#pragma once

#include <string>

#include "component.h"

#include <sol.hpp>

class LuaComponent : public Component
{
public:
    LuaComponent(std::string name) : Component(name) {}

    sol::environment lua;
    sol::state* luaState;

    void init(std::string_view scriptPath, sol::state& state);

    void _on_create() override;
    void _on_destroy() override;

    void populateLuaData();
};