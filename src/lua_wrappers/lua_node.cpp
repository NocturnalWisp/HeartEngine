#include "lua_wrappers/lua_node.h"

void LuaNode::init(std::string_view script)
{
    lua.open_libraries(sol::lib::base);

    // lw_getNodeWrapper(lua, *node.get());

    lua.script(script);
}

void LuaNode::ready()
{
    lua["_ready"]();
}

void LuaNode::update()
{
    lua["_update"]();
}

void LuaNode::draw()
{
    lua["_draw"]();
}

void LuaNode::remove()
{
    lua["_remove"]();
}