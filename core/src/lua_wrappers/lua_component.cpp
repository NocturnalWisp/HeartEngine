#include "lua_wrappers/lua_component.h"

#include "node.h"

void LuaComponent::init(std::string_view scriptPath, sol::state& p_lua)
{
    lua = &p_lua;

    lua->script_file(std::string(scriptPath));
}

void LuaComponent::_on_create()
{
    sol::protected_function _on_create = (*lua)[name]["_on_create"];
    _on_create();
}

void LuaComponent::_on_destroy()
{
    (*lua)[name]["_on_destroy"];
}

void LuaComponent::getLuaData(sol::state& lua)
{
    lua[name]["name"] = &name;
    lua[name]["node"] = node;
}