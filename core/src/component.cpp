#include "component.h"

#include "engine.h"

namespace HeartEngine
{
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
        luaEnv["name"] = &name;
        luaEnv["node"] = node;

        node->engine->fileManager.loadScript(scriptName, *luaState, &luaEnv);
        isLuaScript = true;
    }
    else
    {
        // C++ component.
        // Environment table is set to this component to allow for accessing members.
        setEnvironment();

        isLuaScript = false;
    }

    if (node->engine->started)
    {
        _on_create();
    }
}
}