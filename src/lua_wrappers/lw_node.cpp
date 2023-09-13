#include "lua_wrappers/lw_node.h"

void lw_getNodeWrapper(sol::state& lua, Node& node)
{
    lua.new_usertype<Node>("Node",
        "name", &Node::name,
        "setName", [](Node& self, const char* name){ self.name = name; });

    lua.set("name", node.name);

    // lua.set_function("getNode", &Node::getNodePtr, node);

    
}