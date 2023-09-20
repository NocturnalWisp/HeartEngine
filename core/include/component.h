#pragma once

#include <string>

#include <sol.hpp>

#include "debug.h"

#include "event.h"

class Node;

class Component
{
    friend class Node;
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create() {}
    virtual void _on_destroy() {}

    virtual void getLuaData(sol::state& lua) {  }
};