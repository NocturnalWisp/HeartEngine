#include "lua_wrappers/lua_component.h"

#include "node.h"
#include "engine.h"

void LuaComponent::init(std::string_view scriptPath, sol::state& p_luaState)
{
    lua = sol::environment(p_luaState, sol::create);
    luaState = &p_luaState;

    lua["print"] = p_luaState["print"];

    // Engine::populateBasicLua(lua);
    populateLuaData();

    p_luaState.script_file(std::string(scriptPath), lua);
}

void LuaComponent::_on_create()
{
    lua[name]["_on_create"]();
}

void LuaComponent::_on_destroy()
{
    lua[name]["_on_destroy"]();
}

void LuaComponent::populateLuaData()
{
    lua["name"] = &name;
    lua["node"] = std::ref(node);

    lua["getComponent"] = [this](std::string componentName)
        {
            lua[componentName] = (*luaState)[componentName];
        };
}