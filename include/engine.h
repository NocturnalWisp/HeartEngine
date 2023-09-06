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
    static std::shared_ptr<T> getResource(std::string_view name)
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

    template <typename T>
    node_ptr addNode(T node, node_ptr parent = root, bool make_shared = true)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        if (auto parent_ptr = parent.lock())
        {
            return handle_node(std::make_shared<T>(node), parent_ptr);
        }

        return node_ptr();
    }

    // Always relative to root!
    template <typename T>
    node_ptr addNode(T node, std::string_view path)
    {
        return addNode(node, root->getNode(path));
    }

    node_ptr addNode(std::string registeredType, std::string name, std::string_view parentPath)
    {
        if (nodeRegistry.count(registeredType))
        {
            if (auto parent_ptr = root->getNode(parentPath).lock())
            {
                return handle_node(nodeRegistry[registeredType](name), parent_ptr);
            }
        }
        else
        {
            Debug::printerr("No registered type with the name: ", registeredType);
        }

        return node_ptr();
    }

    void registerNodeType(std::string name, shared_node_ptr(*ctor)(std::string))
    {
        nodeRegistry[name] = ctor;
    }
private:
    inline static bool started = false;
    inline static bool checkResourceRelease = false;

    inline static std::map<std::string, shared_node_ptr(*)(std::string)> nodeRegistry;

    inline static std::vector<std::shared_ptr<Resource>> resources;
    inline static std::shared_ptr<Node> root;

    static void recursiveRun(const shared_node_ptr& node, void (function)(const shared_node_ptr&));

    static void checkEarlyResourceRelease();

    node_ptr handle_node(shared_node_ptr node, shared_node_ptr parent = root)
    {
        parent->addChild(node);

        auto& childPtr = parent->children.back();

        childPtr->root = root;
        childPtr->self = childPtr;

        childPtr->EarlyResourceReleaseCallback = checkEarlyResourceRelease;

        if (started)
        {
            ready(childPtr);
        }

        return childPtr;
    }
};