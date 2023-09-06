#include <sol.hpp>

#include "../../include/node.h"

#include "lw_node.cpp"

template<class T>
class LuaNode
{
    static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");
    shared_node_ptr node;
    sol::state lua;
public:
    LuaNode(shared_node_ptr node) : node(node) {}

    void init(std::string_view script)
    {
        lua.open_libraries(sol::lib::base);

        lw_getNodeWrapper(lua, *node.get());

        lua.script(script);
    }

    void ready()
    {
        lua["_ready"]();
    }

    void update()
    {
        lua["_update"]();
    }

    void draw()
    {
        lua["_draw"]();
    }

    void remove()
    {
        lua["_remove"]();
    }
};