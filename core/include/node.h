#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <type_traits>

#include "debug.h"

#include "component.h"

class Engine;

class Node
{
    friend class Engine;
public:
    Node(std::string p_name) : name(p_name) {}

    Component* getComponent(std::string_view name) const;

    template<typename T>
    T* getComponentT(std::string_view name) const
    {
        static_assert(std::is_convertible<T, Component>::value, "Class must inherit component");
        return static_cast<T*>(getComponent(name));
    }

    template <class T>
    T* addComponent(T c)
    {
        static_assert(std::is_convertible<T, Component>::value, "Class must inherit component");

        auto component = std::make_unique<T>(std::move(c));
        component->node = this;

        auto ptr = component.get();

        components.push_back(std::move(component));

        return ptr;
    }

    virtual Component* addComponent(std::string_view typeName, std::string name);

    void removeComponent(std::string_view name);

    void destroy();

    Engine* engine;

    std::vector<std::unique_ptr<Component>> components;

    std::string name;

private:
    friend void onCreate(Node& node)
    {
        for (auto& component : node.components)
        {
            component->_on_create();
        }
    }
    friend void onDestroy(Node& node)
    {
        for (auto& component : node.components)
        {
            component->_on_destroy();
        }

        node.components.clear();
    }
};