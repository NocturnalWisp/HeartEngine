#pragma once

#include <string>

#include <sol/sol.hpp>

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

    virtual void populateLuaData() override = 0;

    Node* node;

    std::string name;

    virtual void _on_create();
    virtual void _on_destroy();
private:
    void setupLuaState(sol::state& state, std::string scriptName = "") override;
    void populateEnvironment() override;

    bool isLuaScript = false;
};

class LuaComponent : public Component
{
public:
    LuaComponent(std::string name) : Component(name) {}

    void populateLuaData() override {}
};
}