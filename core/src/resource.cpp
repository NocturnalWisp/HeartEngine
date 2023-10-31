#include "heart/resource.h"

#include "heart/engine.h"

namespace HeartEngine
{
void Resource::_on_load()
{
    luaEnv["_on_load"]();
}
void Resource::_on_unload()
{
    luaEnv["_on_unload"]();
}

void Resource::setupLuaState(sol::state& state, std::string scriptName)
{
    luaState = &state;

    // Create lua environment.
    luaEnv = sol::environment(*luaState, sol::create, luaState->globals());

    if (scriptName.compare("") != 0)
    {
        // Lua Scripted Component
        luaEnv["name"] = &name;
        luaEnv["engine"] = engine;

        engine->fileManager.loadScript(scriptName, *luaState, &luaEnv);
        isLuaScript = true;
    }
    else
    {
        // C++ component.
        // Environment table is set to this resource to allow for accessing members.
        setEnvironment();

        isLuaScript = false;
    }
}
}