#pragma once

#include <sol.hpp>

class Node;

class Component
{
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create() {}
    virtual void _on_destroy() {}

    virtual void getLuaData(sol::state& lua, std::string_view tableName) {  }
};