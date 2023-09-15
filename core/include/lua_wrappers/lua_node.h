#pragma once

#include <string>

#include <sol.hpp>

#include "node.h"
#include "Engine.h"

class LuaNode : public Node
{
public:
    LuaNode(std::string name) : Node(name) {}

    void init(const std::string& scriptPath);

    sol::state lua;

    Component* addComponent(std::string_view typeName, std::string name) override;
private:
    void populate();
};