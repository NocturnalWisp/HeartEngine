#pragma once

#include <string>

namespace sol { class state; }

class Node;

class Component
{
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create() {}
    virtual void _on_destroy() {}

    virtual void getLuaData(sol::state& lua) {  }
};