#include "global_data.h"

#include "engine.h"

namespace HeartEngine
{
void GlobalData::_on_load()
{
    luaEnv["_on_load"]();
}

void GlobalData::_on_unload()
{
    luaEnv["_on_unload"]();
}

void GlobalData::setupLuaState(sol::state& p_luaState, std::string scriptName)
{
    luaState = &p_luaState;

    // Create lua environment.
    luaEnv = sol::environment(*luaState, sol::create, luaState->globals());

    populateEnvironment();

    if (scriptName.compare("") != 0)
    {
        // Lua Global Data
        engine->fileManager.loadScript(scriptName, *luaState, &luaEnv);

        // Set a table up in the main state for quick and easy access as global data.
        (*luaState)[name] = luaEnv;
    }
    else
    {
        // C++ Global Data
        luaEnv[name] = this;

        (*luaState)[name] = luaEnv[name];
    }

    if (engine->started)
    {
        _on_load();
    }
}

void GlobalData::populateEnvironment()
{
    luaEnv["name"] = &name;
    luaEnv["engine"] = engine;
}
}