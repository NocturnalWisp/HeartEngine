#include "component.h"

#include "engine.h"

void Component::_on_create()
{
    luaEnv["_on_create"]();
}

void Component::_on_destroy()
{
    luaEnv["_on_destroy"]();
}

void Component::setupLuaState(sol::state& p_luaState, std::string scriptName)
{
    luaState = &p_luaState;

    // Create lua environment.
    luaEnv = sol::environment(*luaState, sol::create, luaState->globals());

    if (scriptName.compare("") != 0)
    {
        // Lua Scripted Component
        populateEnvironment();
        luaState->script_file(scriptName, luaEnv);
    }
    else
    {
        // C++ component.
        populateLuaData();
    }

    if (node->engine->started)
    {
        _on_create();
    }
}

void Component::populateEnvironment()
{
    luaEnv["name"] = &name;
    luaEnv["node"] = node;
}
