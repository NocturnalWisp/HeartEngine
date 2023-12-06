#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <type_traits>
#include <chrono>

#include <sol/sol.hpp>

#include "debug.h"

#include "file_manager.h"

#include "module.h"

#include "resource.h"
#include "global_data.h"
#include "node.h"

#include "event.h"

#include "draw_mode.h"

namespace HeartEngine
{
class Engine
{
    friend class Node;
    friend class Container;
    friend class Component;
    friend class Resource;
public:
    Engine();

    void init();
    void run();

    template<class T>
    T* registerModule(T moduleObject)
    {
        static_assert(std::is_base_of<Module, T>::value, "T must derive from Module.");

        std::unique_ptr<T> module = std::make_unique<T>(std::move(moduleObject));

        auto modulePtr = module.get();

        moduleRegistry.push_back(std::move(module));

        modulePtr->registerTypes(*this, *lua);

        return modulePtr;
    }

    Node* getNode(std::string_view name);

    template <class T>
    T* addNode(std::string nodeName, Container* container = nullptr, std::string scriptName = "")
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        std::unique_ptr<Node> node = std::unique_ptr<Node>(new T(nodeName));

        T* nodePtr = static_cast<T*>(node.get());

        if (container != nullptr)
        {
            container->nodes.push_back(std::move(node));
        }
        else
        {
            nodes.push_back(std::move(node));
        }

        nodePtr->engine = this;

        nodePtr->setupLuaState(*lua.get(), scriptName);

        return nodePtr;
    }

    bool removeNode(std::string_view name);

    Resource& loadResource(std::string_view typeName, std::string name, sol::variadic_args args);

    template <typename T>
    std::shared_ptr<Resource> loadResource(T resource, std::string scriptName = "")
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        auto res = std::make_shared<T>(resource);

        res->engine = this;
        res->setupLuaState(*lua, scriptName);

        // Makes another shared_ptr here.
        resources.push_back(res);

        // Makes another shared_ptr here. (But goes away at EOF.)
        load(res);

        // Returns the shared_ptr created in this function.
        return std::move(res);
    }

    std::shared_ptr<Resource> getResource(std::string_view name) const;

    template <typename T>
    std::shared_ptr<T> getResourceT(std::string_view name)
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

    // Resource Registry.
    template <typename T>
    sol::usertype<T> registerResource(std::string typeName,
        std::shared_ptr<Resource>(*creator)(std::string, sol::variadic_args))
    {
        resourceRegistry[typeName] = creator;

        return lua->new_usertype<T>(typeName);
    }

    template <class T>
    static std::shared_ptr<Resource> resourceBuilder(std::string name, sol::variadic_args va)
    {
        static_assert(std::is_base_of<Resource, T>::value, "Type must inherit from resource.");
        return std::make_shared<T>(T(name, va));
    }

    std::shared_ptr<Resource> getResourceFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va);

    // Global Data Registry.
    template <class T>
    T* registerGlobalData(T globalDataObject, std::string scriptName = "")
    {
        static_assert(std::is_base_of<GlobalData, T>::value, "Class must derive from Global Data.");

        std::unique_ptr<T> globalData = std::make_unique<T>(std::move(globalDataObject));

        auto globalDataPtr = globalData.get();

        globalDataObjects.push_back(std::move(globalData));

        globalDataPtr->engine = this;

        globalDataPtr->setupLuaState(*lua.get(), scriptName);

        return globalDataPtr;
    }

    GlobalData* getGlobalData(std::string_view name) const;

    template<class T>
    T* getGlobalDataT(std::string_view name) const
    {
        static_assert(std::is_convertible<T, GlobalData>::value, "Class must derive from Global Data.");
        return static_cast<T*>(getGlobalData(name));
    }

    // Component Registry.
    template <typename T>
    sol::usertype<T> registerComponent(std::string typeName,
        std::unique_ptr<Component>(*creator)(std::string, sol::variadic_args))
    {
        componentRegistry[typeName] = creator;

        return lua->new_usertype<T>(typeName);
    }

    template <class T>
    static std::unique_ptr<Component> componentBuilder(std::string name, sol::variadic_args va)
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component.");
        return std::make_unique<T>(T(name, va));
    }

    std::unique_ptr<Component> getComponentFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va);

    // Draw Mode
    void registerDrawMode(std::string name, std::unique_ptr<DrawMode> drawMode);
    void unregisterDrawMode(std::string name);

    double getTime()
    {
        return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
    }

    FileManager fileManager = {};

    bool started = false;

    // Events
    EventManager events;

    bool shouldCloseWindow = false;

    double deltaTime;

private:
    void populateBasicLua();
    void checkEarlyResourceRelease();

    std::unique_ptr<sol::state> lua;

    bool checkResourceRelease = false;

    std::vector<std::shared_ptr<Resource>> resources;
    std::vector<std::unique_ptr<GlobalData>> globalDataObjects;
    std::vector<std::unique_ptr<Node>> nodes;

    std::vector<std::unique_ptr<Module>> moduleRegistry;
    std::map<std::string, std::unique_ptr<Component>(*)(std::string name, sol::variadic_args va)> componentRegistry;
    std::map<std::string, std::shared_ptr<Resource>(*)(std::string name, sol::variadic_args va)> resourceRegistry;

    std::map<std::string, std::unique_ptr<DrawMode>> drawModeRegistry;

    std::chrono::_V2::system_clock::time_point startTime = std::chrono::system_clock::now();

    const double MS_PER_UPDATE = 0.01;
};
}