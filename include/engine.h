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
    friend class ResourceBase;
private:
    inline static std::unique_ptr<Engine> singleton;
public:
    static Engine& create();

    static int run();

    static node_ptr getRoot();

    Engine& inlineDoSomething(void(*something)());

    template <typename T>
    Engine& loadResource(T resource)
    {
        static_assert(std::is_base_of<ResourceBase, T>::value, "T must derive from Resource.");

        auto res = std::make_shared<T>(resource);

        resources.push_back(res);

        load(res);

        return *this;
    }

    template <typename T>
    static std::shared_ptr<T> getResource(const char* name)
    {
        static_assert(std::is_base_of<ResourceBase, T>::value, "T must derive from Resource.");

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
    Engine& addNode(T node, node_ptr parent = root)
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
                runReady(childPtr);
            }
        }

        return *this;
    }

    // Always relative to root!
    template <typename T>
    Engine& addNode(T node, const char* path)
    {
        addNode(node, root->getNode(path));

        return *this;
    }
private:
    inline static bool started = false;
    inline static bool checkResourceRelease = false;

    inline static std::vector<std::shared_ptr<ResourceBase>> resources;
    inline static std::shared_ptr<Node> root;

    static void recursiveRun(const shared_node_ptr& node, void (function)(const shared_node_ptr&));

    static void checkEarlyResourceRelease();
};