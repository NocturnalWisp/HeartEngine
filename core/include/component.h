#pragma once

#include <string>

#include <sol.hpp>

#include "debug.h"

#include "event.h"

class Engine;
class Node;

class Component
{
    friend class Engine;
    friend class Node;
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create();
    virtual void _on_destroy();

    virtual void populateLuaData() {  }
protected:
    sol::environment luaEnv;
private:
    void setupLuaState(sol::state& state, std::string scriptName);
    void populateEnvironment();

    sol::state* luaState;
};