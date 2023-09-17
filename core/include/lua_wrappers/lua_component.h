#pragma once

#include <string>

#include "component.h"

namespace sol { class state; }

class LuaComponent : public Component
{
public:
    LuaComponent(std::string name) : Component(name) {}

    sol::state* lua;

    void init(std::string_view scriptPath, sol::state& lua);

    void _on_create() override;
    void _on_destroy() override;

    void getLuaData(sol::state& lua) override;
};