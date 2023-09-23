#pragma once

#include <string>

#include <sol.hpp>

#include "lua_environment.h"

namespace HeartEngine
{
class Engine;

class GlobalData : public LuaEnvironment
{
    friend class Engine;
public:
    GlobalData(std::string name) : name(name) {}

    virtual void _on_load();
    virtual void _on_unload();

    Engine* engine;

    std::string name;
private:
    void setupLuaState(sol::state& state, std::string scriptName = "") override;
    void populateEnvironment() override;
};
}