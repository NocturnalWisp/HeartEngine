#include "lua_wrappers/lua_node.h"

void LuaNode::init(std::string_view script)
{
    lua.open_libraries(sol::lib::base);

    populate();

    lua.script(script);
}

void LuaNode::_on_create()
{
    lua["_on_create"]();
}

void LuaNode::_on_destroy()
{
    lua["_on_destroy"]();
}

Component* LuaNode::addComponent(std::string_view typeName, std::string name)
{
    auto ptr = Node::addComponent(typeName, name);

    ptr->getLuaData(lua, name);

    return ptr;
}

void LuaNode::populate()
{
    lua.new_usertype<Node>("Node",
        "name", &Node::name,
        "getComponent", &Node::getComponent,
        "addComponent", [this](std::string_view typeName, std::string name, sol::table args) -> Component*
            { return addComponent(typeName, name); }
    );

    lua.new_usertype<Component>("Component",
        "name", &Component::name,
        "node", &Component::node
    );

    lua.set("name", &name);
    lua.set_function("getComponent", &Node::getComponent, this);
    lua.set_function("addComponent",
        [this](std::string_view typeName, std::string name)
        { addComponent(typeName, name); });
}