#pragma once

#include <string>

#include <sol/sol.hpp>

namespace HeartEngine
{
class LuaEnvironment
{
public:
    sol::state* luaState;
    sol::environment luaEnv;
private:
    virtual void setupLuaState(sol::state& state, std::string scriptName = "") = 0;
};
}