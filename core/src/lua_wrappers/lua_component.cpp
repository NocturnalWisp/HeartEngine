#include "lua_wrappers/lua_component.h"
#include "engine.h"

#include <fstream>

void LuaComponent::init(std::string_view scriptPath)
{
    lua.open_libraries(sol::lib::base);

    Engine::populateBasicLua(lua);
    populate();

    lua.script_file(std::string(scriptPath));
}

void LuaComponent::_on_create()
{
    lua["_on_create"]();
}

void LuaComponent::_on_destroy()
{
    lua["_on_destroy"]();
}

void LuaComponent::getLuaData(sol::state& otherLua, std::string_view tableName)
{
    //TODO: May not work!
    // lua[tableName] = ;
}

void LuaComponent::populate()
{
    lua.set("name", &name);
    lua.set("node", node);
}