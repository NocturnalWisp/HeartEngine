#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <tuple>
#include <functional>

#include <raylib.h>
#include <raymath.h>

#include "../include/debug.h"
#include "../include/node.h"
#include "../include/resource.h"

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class Engine
{
    friend class Node;
    friend class Resource;
public:
    Engine();

    int run();

    static node_ptr getRoot();

    template <typename T>
    void loadResource(T resource)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        auto res = std::make_shared<T>(resource);

        resources.push_back(res);

        load(res);
    }

    template <typename T>
    static std::shared_ptr<T> getResource(const char* name)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        std::shared_ptr<T> found = nullptr;

        for (auto res : resources)
        {
            if (strcmp(res->name.c_str(), name) == 0)
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

    template <typename T>
    node_ptr addNode(T node, node_ptr parent = root)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        if (auto parent_ptr = parent.lock())
        {
            parent_ptr->addChild(std::make_shared<T>(node));

            auto& childPtr = parent_ptr->children.back();

            childPtr->root = root;
            childPtr->self = childPtr;

            childPtr->EarlyResourceReleaseCallback = checkEarlyResourceRelease;

            if (started)
            {
                ready(childPtr);
            }

            return childPtr;
        }

        return node_ptr();
    }

    // Always relative to root!
    template <typename T>
    node_ptr addNode(T node, const char* path)
    {
        return addNode(node, root->getNode(path));
    }
private:
    inline static bool started = false;
    inline static bool checkResourceRelease = false;

    inline static std::vector<std::shared_ptr<Resource>> resources;
    inline static std::shared_ptr<Node> root;

    static void recursiveRun(const shared_node_ptr& node, void (function)(const shared_node_ptr&));

    static void checkEarlyResourceRelease();
};