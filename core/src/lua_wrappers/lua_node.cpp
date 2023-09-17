#include "lua_wrappers/lua_node.h"

#include "lua_wrappers/lua_component.h"
#include "engine.h"

void LuaNode::init(const std::string& scriptPath)
{
    lua.open_libraries(sol::lib::base);

    Engine::populateBasicLua(lua);
    populate();

    lua.load_file(scriptPath)();
}

Component* LuaNode::addComponent(std::string_view typeName, std::string name)
{
    auto ptr = Node::addComponent(typeName, name);

    ptr->getLuaData(lua);

    return ptr;
}

Component* LuaNode::addLuaComponent(std::string_view scriptPath, std::string name)
{
    auto ptr = Node::addComponent(LuaComponent(name));

    ptr->init(scriptPath, lua);

    ptr->getLuaData(lua);

    return ptr;
}

void LuaNode::populate()
{
    lua.set("name", &name);
    lua.set_function("getComponent", &Node::getComponent, this);
    lua.set_function("addComponent",
        [this](std::string_view typeName, std::string name)
        { addComponent(typeName, name); });
    lua.set_function("addLuaComponent",
        [this](std::string_view scriptName, std::string name)
        { addLuaComponent(scriptName, name); });
}