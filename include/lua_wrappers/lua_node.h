#pragma once

#include <string>

#include <sol.hpp>

#include "node.h"
#include "Engine.h"

#include "lw_node.h"

class LuaNode : public Node
{
public:
    LuaNode(std::string name) : Node(name) {}

    void init(std::string_view script);

    sol::state lua;

    Component* addComponent(std::string_view typeName, std::string name) override;
private:
    void populate();
};