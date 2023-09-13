#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <tuple>
#include <functional>
#include <map>

#include <raylib.h>
#include <raymath.h>

#include <eventpp/callbacklist.h>

#include "debug.h"
#include "node.h"
#include "resource.h"

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

    Node* addNode(Node n)
    {
        std::unique_ptr<Node> node = std::make_unique<Node>(std::move(n));
        node->engine = this;
        node->EarlyResourceReleaseCallback = checkEarlyResourceRelease;

        if (started)
        {
            onCreate(*node.get());
        }

        auto ptr = node.get();

        nodes.push_back(std::move(node));

        return ptr;
    }

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

    // Events
    eventpp::CallbackList<void()> updateEvent;
    eventpp::CallbackList<void()> drawEvent;
private:
    bool started = false;
    bool checkResourceRelease = false;

    std::vector<std::shared_ptr<Resource>> resources;
    std::vector<std::unique_ptr<Node>> nodes;

    // static void recursiveRun(const shared_node_ptr& node, void (function)(const shared_node_ptr&));

    void checkEarlyResourceRelease();

    // node_ptr handle_node(shared_node_ptr node, shared_node_ptr parent = root)
    // {
    //     parent->addChild(node);

    //     auto& childPtr = parent->children.back();

    //     childPtr->root = root;
    //     childPtr->self = childPtr;

    //     childPtr->EarlyResourceReleaseCallback = checkEarlyResourceRelease;

    //     if (started)
    //     {
    //         ready(childPtr);
    //     }

    //     return childPtr;
    // }
};