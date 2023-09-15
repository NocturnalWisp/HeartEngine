#pragma once

#include <string>

#include <sol.hpp>

#include "component.h"

class LuaComponent : public Component
{
public:
    LuaComponent(std::string name) : Component(name) {}

    void init(std::string_view scriptPath);

    void _on_create() override;
    void _on_destroy() override;

    sol::state lua;

    void getLuaData(sol::state& lua, std::string_view tableName) override;
private:
    void populate();
};