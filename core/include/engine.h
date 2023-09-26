#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <type_traits>

#include <sol/sol.hpp>

#include "debug.h"

#include "file_manager.h"

#include "module.h"

#include "resource.h"
#include "global_data.h"
#include "node.h"

#include "event.h"

namespace HeartEngine
{
constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class Engine
{
    friend class Node;
    friend class Component;
    friend class Resource;
public:
    Engine();

    int run();

    template<class T>
    T* registerModule(T moduleObject)
    {
        static_assert(std::is_base_of<Module, T>::value, "T must derive from Module.");

        std::unique_ptr<T> module = std::make_unique<T>(std::move(moduleObject));

        auto modulePtr = module.get();

        moduleRegistry.push_back(std::move(module));

        modulePtr->engine = this;

        modulePtr->registerTypes();

        return modulePtr;
    }

    Node* getNode(std::string_view name);

    template <class T>
    T* addNode(T nodeObject, std::string scriptName = "")
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        std::unique_ptr<T> node = std::make_unique<T>(std::move(nodeObject));

        auto nodePtr = node.get();

        nodes.push_back(std::move(node));

        nodePtr->engine = this;

        nodePtr->setupLuaState(*lua.get(), scriptName);

        return nodePtr;
    }

    bool removeNode(std::string_view name);

    template <typename T>
    void loadResource(T resource)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        auto res = std::make_shared<T>(resource);

        res->engine = this;

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

    void registerComponent(std::string typeName, std::unique_ptr<Component>(*creator)(std::string, sol::variadic_args));

    std::unique_ptr<Component> getComponentFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va);

    template <class T>
    static std::unique_ptr<Component> registerComponentType(std::string name, sol::variadic_args va)
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component.");
        return std::make_unique<T>(T(name, va));
    }

    FileManager fileManager = {};

    bool started = false;

    // Events
    EventBus updateEvent;
    EventBus drawEvent;
private:
    void populateBasicLua();
    void checkEarlyResourceRelease();

    std::unique_ptr<sol::state> lua;

    bool checkResourceRelease = false;

    std::vector<std::shared_ptr<Resource>> resources;
    std::vector<std::unique_ptr<GlobalData>> globalDataObjects;
    std::vector<std::unique_ptr<Node>> nodes;

    std::map<std::string, std::unique_ptr<Component>(*)(std::string name, sol::variadic_args va)> componentRegistry;
    std::vector<std::unique_ptr<Module>> moduleRegistry;
};
}