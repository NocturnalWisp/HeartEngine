#pragma once

#include <string>

#include <sol.hpp>

#include "debug.h"

#include "event.h"

#include "lua_environment.h"

namespace HeartEngine
{
class Engine;
class Node;

class Component : public LuaEnvironment
{
    friend class Engine;
    friend class Node;
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create();
    virtual void _on_destroy();
private:
    void setupLuaState(sol::state& state, std::string scriptName = "") override;
    void populateEnvironment() override;
};
}