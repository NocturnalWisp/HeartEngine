#include "lua_wrappers/lua_node.h"

#include "lua_wrappers/lua_component.h"
#include "engine.h"

void LuaNode::init(const std::string& scriptPath)
{
    lua.open_libraries(sol::lib::base);

    // Engine::populateBasicLua(lua);
    populate();

    lua.load_file(scriptPath)();
}

// Component* LuaNode::addComponent(std::string_view typeName, std::string name)
// {
//     auto ptr = Node::addComponent(typeName, name);

//     ptr->populateLuaData();

//     return ptr;
// }

Component* LuaNode::addLuaComponent(std::string_view scriptPath, std::string name)
{
    auto ptr = Node::addComponent(LuaComponent(name));

    ptr->init(scriptPath, lua);

    lua[name] = ptr->lua[name];

    return ptr;
}

void LuaNode::populate()
{

    lua.set("name", &name);
    lua["engine"] = engine;

    lua.set_function("addComponent",
        [this](std::string_view typeName, std::string name)
        { addComponent(typeName, name); });
    lua.set_function("addLuaComponent",
        [this](std::string_view scriptName, std::string name)
        { addLuaComponent(scriptName, name); });

    lua.set_function("addEventListener",
        [this](std::string eventName, sol::function function) -> EventHandle*
        {
            return addEventListener(eventName, [function](sol::object obj1, sol::object obj2){ function(obj1, obj2); });
        });
    lua.set_function("runEvent", static_cast<void(Node::*)(std::string)>(&Node::runEvent), this);
    lua.set_function("runEvent", static_cast<void(Node::*)(std::string, sol::object)>(&Node::runEvent), this);
    lua.set_function("runEvent", static_cast<void(Node::*)(std::string, sol::object, sol::object)>(&Node::runEvent), this);
}