#pragma once

#include <string>

#include "node.h"

#include <sol.hpp>

typedef void (*LuaComponentFunctionCallback)(std::string_view componentName, std::string_view functionName);

class LuaNode : public Node
{
public:
    LuaNode(std::string name) : Node(name) { }

    void init(const std::string& scriptPath);

    sol::state lua;

    Component* addComponent(std::string_view typeName, std::string name) override;
    Component* addLuaComponent(std::string_view scriptName, std::string name);
private:
    void populate();
};