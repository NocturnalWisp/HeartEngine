#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <type_traits>

#include <raylib.h>
#include <raymath.h>

#include "debug.h"

class Engine;
class Node;

// typedef struct RotationAxisAngle
// {
//     Vector3 axis;
//     float   angle;
// } RotationAxisAngle;

class Component
{
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create() {}
    virtual void _on_destroy() {}

    virtual void registerLuaData() {}
};

class Node
{
    friend class Engine;
public:
    Node(std::string p_name) : name(p_name) {}

    template <class T>
    T* getComponent(std::string_view name) const
    {
        static_assert(std::is_convertible<T, Component>::value, "Class must inherit component");
        Component* foundComponent;

        for (const auto& component : components)
        {
            if (component->name.compare(name) == 0)
            {
                foundComponent = component.get();
            }
        }

        return foundComponent;
    }

    template <class T>
    void addComponent(T component)
    {
        static_assert(std::is_convertible<T, Component>::value, "Class must inherit component");
        component.node = this;
        components.push_back(std::make_unique<T>(component));
    }

    void destroy();

    Engine* engine;

    std::vector<std::unique_ptr<Component>> components;

    std::string name;
protected:
    virtual void _on_create() {}
    virtual void _on_destroy() {}
private:
    // Engine callbacks
    void(Engine::*EarlyResourceReleaseCallback)();

    friend void onCreate(Node& node)
    {
        for (auto& component : node.components)
        {
            component->_on_create();
        }

        node._on_create();
    }
    friend void onDestroy(Node& node)
    {
        for (auto& component : node.components)
        {
            component->_on_destroy();
        }

        node._on_destroy();

        node.components.clear();
    }
};


//TODO:
// Borrowed liberally from https://github.com/juniper-dusk/raylib-transform
// Awesome library thank you Juniper!