#pragma once

#include <sol.hpp>

#include "node.h"

#include "lw_node.h"

class LuaNode
{
public:
    LuaNode(shared_node_ptr node) : node(node) {}

    void init(std::string_view script);

    void ready();
    void update();
    void draw();
    void remove();

    sol::state lua;
private:
    shared_node_ptr node;
};