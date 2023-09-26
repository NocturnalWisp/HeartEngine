#pragma once

#include <string>

#include <sol/sol.hpp>

namespace HeartEngine
{
#define CREATEUSERTYPE(t)\
    luaState->new_usertype<t>(__STRINGIFY(t));\
    luaEnv[name] = this

class LuaEnvironment
{
public:
    virtual void populateLuaData() {}

    sol::state* luaState;
    sol::environment luaEnv;
private:
    virtual void setupLuaState(sol::state& state, std::string scriptName = "") = 0;
    virtual void populateEnvironment() = 0;
};
}