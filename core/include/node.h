#pragma once

#include <vector>
#include <string>
#include <memory>
#include <type_traits>

#include <sol.hpp>

#include "debug.h"

#include "event.h"

#include "component.h"

class Engine;

class Node
{
    friend class Engine;
    friend class Component;
public:
    Node(std::string p_name) : name(p_name) {}

    template <class T>
    T* addComponent(T c, std::string scriptName = "")
    {
        static_assert(std::is_convertible<T, Component>::value, "Class must inherit component");

        auto component = std::make_unique<T>(std::move(c));

        auto componentPtr = component.get();

        components.push_back(std::move(component));

        componentPtr->node = this;

        componentPtr->setupLuaState(*luaState, scriptName);

        return componentPtr;
    }

    Component* getComponent(std::string_view name) const;

    template<class T>
    T* getComponentT(std::string_view name) const
    {
        static_assert(std::is_convertible<T, Component>::value, "Class must inherit component");
        return static_cast<T*>(getComponent(name));
    }

    Component* addComponent(std::string_view typeName, std::string name);
    void removeComponent(std::string_view name);

    void destroy();

    virtual void onCreate();
    virtual void onDestroy();

    Engine* engine;

    std::vector<std::unique_ptr<Component>> components;

    std::string name;

public:
    EventHandle* addEventListener(std::string eventName, std::function<void()>);
    EventHandle* addEventListener(std::string eventName, std::function<void(sol::object)>);
    EventHandle* addEventListener(std::string eventName, std::function<void(sol::object, sol::object)>);

    void removeEventListener(std::string eventName, EventHandle& handle);

    void runEvent(std::string eventName);
    void runEvent(std::string eventName, sol::object);
    void runEvent(std::string eventName, sol::object, sol::object);

    void deleteEvent(std::string eventName);
private:
    void setupLuaState(sol::state& state, std::string scriptName);
    void populateEnvironment();

    sol::state* luaState;
    sol::environment luaEnv;

    EventManager events;
};