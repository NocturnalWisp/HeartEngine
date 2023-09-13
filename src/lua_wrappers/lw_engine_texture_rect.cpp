#include "lua_wrappers/lw_engine_texture_rect.h"

#include "components/engine_texture_rect.h"

void lw_getEngineTextureRectWrapper(sol::state& lua, Node& node)
{
    lw_getNodeWrapper(lua, node);

    // lua.new_usertype<EngineTextureRect>("Node",
    //     "name", &Node::name,
    //     "setName", [](Node& self, const char* name){ self.name = name; });

    lua.set("name", node.name);

    // lua.set_function("getNode", &Node::getNodePtr, node);
}