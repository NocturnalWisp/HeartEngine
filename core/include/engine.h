#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <type_traits>

#include "debug.h"
#include "node.h"

#include "resource.h"

#include "event.h"

namespace sol { class state; }

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class Engine
{
    friend class Node;
    friend class Resource;
public:
    Engine();

    int run();

    Node* getNode(std::string_view name);

    template <class T>
    T* addNode(T n)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        std::unique_ptr<T> node = std::make_unique<T>(std::move(n));
        node->engine = this;

        if (started)
        {
            node->onCreate();
        }

        auto ptr = node.get();

        nodes.push_back(std::move(node));

        return ptr;
    }

    bool removeNode(std::string_view name);

    template <typename T>
    void loadResource(T resource)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        auto res = std::make_shared<T>(resource);

        resources.push_back(res);

        load(res);
    }

    template <typename T>
    std::shared_ptr<T> getResource(std::string_view name)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        std::shared_ptr<T> found = nullptr;

        for (auto res : resources)
        {
            if (res->name.compare(name) == 0)
            {
                found = std::dynamic_pointer_cast<T>(res);

                if (!found->loaded)
                {
                    load(found);
                }

                break;
            }
        }

        return found;
    }

    std::unique_ptr<Component> getComponentFromRegistry(std::string_view typeName, std::string name);

    void registerComponent(std::string typeName, std::unique_ptr<Component>(*creator)(std::string name));

    // Events
    EventBus updateEvent;
    EventBus drawEvent;

    static void populateBasicLua(sol::state& lua);
private:
    bool started = false;
    bool checkResourceRelease = false;

    std::vector<std::shared_ptr<Resource>> resources;
    std::vector<std::unique_ptr<Node>> nodes;

    std::map<std::string, std::unique_ptr<Component>(*)(std::string name)> componentRegistry;

    void checkEarlyResourceRelease();
};