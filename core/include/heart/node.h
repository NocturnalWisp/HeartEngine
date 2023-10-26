#pragma once

#include <vector>
#include <string>
#include <memory>
#include <type_traits>

#include <cassert>

#include <sol/sol.hpp>

#include "debug.h"

#include "event.h"

#include "lua_environment.h"
#include "component.h"

namespace HeartEngine
{
class Engine;
class Container;

class Node : LuaEnvironment
{
    friend class Engine;
    friend class Component;
    friend class Container;
public:
    template <class T>
    T* addComponent(T c, std::string scriptName = "")
    {
        static_assert(std::is_base_of<Component, T>::value, "Class must inherit component");

        auto component = std::make_unique<T>(std::move(c));

        auto componentPtr = component.get();

        components.push_back(std::move(component));

        componentPtr->node = this;
        componentPtr->setupLuaState(*luaState, scriptName);

        return componentPtr;
    }

    Component& getComponent(std::string_view name) const;

    template<class T>
    T& getComponentT(std::string_view name) const
    {
        static_assert(std::is_base_of<Component, T>::value, "Class must inherit component");
        return static_cast<T&>(getComponent(name));
    }

    Component& addComponent(std::string_view typeName, std::string name, sol::variadic_args va);
    void removeComponent(std::string_view name);

    void destroy();

    virtual void onCreate();
    virtual void onDestroy();

    Engine* engine;

    std::vector<std::unique_ptr<Component>> components;

    std::string name;

    EventManager events;

private:
    Node(std::string p_name) : name(p_name) {}

    void setupLuaState(sol::state& state, std::string scriptName);
    void populateEnvironment();

    sol::state* luaState;
    sol::environment luaEnv;
};

// Allow better organization for nodes.
class Container : private Node
{
    friend class Engine;
    friend class Node;
public:
    EventManager events;
private:
    Container(std::string p_name) : Node(p_name) {}

    void onCreate() override
    {
        for (auto& node : nodes)
        {
            node->onCreate();
        }
    }

    void onDestroy() override
    {
        for (auto& node : nodes)
        {
            node->onDestroy();
        }
    }

    std::vector<std::unique_ptr<Node>> nodes;
};
}