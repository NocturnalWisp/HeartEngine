#include "engine.h"

#include <algorithm>
#include <functional>

#include <raylib-cpp.hpp>
#include <raymath.h>

namespace HeartEngine
{
Engine::Engine()
{
    SetTraceLogLevel(4);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);

    lua = std::make_unique<sol::state>(sol::state());
    lua->open_libraries(sol::lib::base);

    populateBasicLua();
}

int Engine::run()
{
    started = true;

    // Creation
    for (auto& node : nodes)
    {
        node->onCreate();
    }

    if (checkResourceRelease)
        checkEarlyResourceRelease();

    while (!WindowShouldClose())
    {
        // Update
        updateEvent.run();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw
        drawEvent.run();

        EndDrawing();

        // Handle hanging resources
        //TODO: Iterating on the list every loop is especially unessecary.
        if (checkResourceRelease)
            checkEarlyResourceRelease();
    }

    // Destruction
    for (auto& node : nodes)
    {
        node->onDestroy();
    }

    for (auto& res : resources)
    {
        unload(res);
    }

    CloseWindow();

    return 0;
}

Node* Engine::getNode(std::string_view name)
{
    Node* foundNode;

    for (const auto& node : nodes)
    {
        if (node->name.compare(name) == 0)
        {
            foundNode = node.get();
        }
    }

    return foundNode;
}

bool Engine::removeNode(std::string_view name)
{
    auto it = std::remove_if(nodes.begin(), nodes.end(),
        [name](const std::unique_ptr<Node>& node){ return node->name.compare(name) == 0; });
    bool any_change = it != nodes.end();
    nodes.erase(it, nodes.end());
    return any_change;
}

template <> Node* Engine::addNode(Node n, std::string);

std::unique_ptr<Component> Engine::getComponentFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va)
{
    for (const auto &componentType : componentRegistry)
    {
        if (componentType.first.compare(typeName) == 0)
        {
            return componentType.second(name, va);
        }
    }

    return nullptr;
}

void Engine::registerComponent(std::string typeName, std::unique_ptr<Component>(*creator)(std::string, sol::variadic_args))
{
    componentRegistry[typeName] = creator;
}

GlobalData* Engine::getGlobalData(std::string_view name) const
{
    GlobalData *foundGlobalData;

    for (const auto &globalDataObject : globalDataObjects)
    {
        if (globalDataObject->name.compare(name) == 0)
        {
            foundGlobalData = globalDataObject.get();
        }
    }

    return foundGlobalData;
}

void Engine::populateBasicLua()
{
    // Engine
    auto engineType = lua->new_usertype<Engine>("Engine");

    engineType["getNode"] = &Engine::getNode;
    engineType["addNode"] = [](Engine& self, std::string name) -> Node*
        { return self.addNode<Node>(Node(name)); };
    engineType["addLuaNode"] = [](Engine& self, std::string scriptName, std::string name) -> Node*
        { return self.addNode<Node>(Node(name), scriptName); };
    engineType["removeNode"] = &Engine::removeNode;

    // Node
    auto nodeType = lua->new_usertype<Node>("Node");

    nodeType["name"] = &Node::name;
    nodeType["addComponent"] = [](Node& self, std::string_view typeName, std::string name, sol::variadic_args va)
        { self.addComponent(typeName, name, va); },
    //TODO: add child class LuaComponent to user type
    // nodeType["addLuaComponent"] = [](Node& self, std::string_view typeName, std::string name, sol::table args)
    //     { self.addLuaComponent(typeName, name); },
    nodeType["getComponent"] =
        [](Node& self, std::string_view component) -> sol::table
        {
            return self.getComponent(component)->luaEnv;
        };
    // lua.set_function("addLuaComponent",
    //     [this](std::string_view scriptName, std::string name)
    //     { addLuaComponent(scriptName, name); });

    //TODO: remove component should remove any table usage.
    // nodeType["removeComponent"] = &Node::removeComponent;
    nodeType["engine"] = &Node::engine;

    nodeType["addEventListener"] = [](Node& self, std::string eventName, sol::function function) -> EventHandle*
        {
            return self.addEventListener(eventName, [function](sol::object obj1, sol::object obj2){ function(obj1, obj2); });
        };
    nodeType["removeEventListener"] = &Node::removeEventListener;
    nodeType["runEvent"] = static_cast<void(Node::*)(std::string)>(&Node::runEvent);
    nodeType["runEvent"] = static_cast<void(Node::*)(std::string, sol::object)>(&Node::runEvent);
    nodeType["runEvent"] = static_cast<void(Node::*)(std::string, sol::object, sol::object)>(&Node::runEvent);

    // Other
    lua->new_usertype<Vector3>("Vector3",
        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z
    );
}

void Engine::checkEarlyResourceRelease()
{
    for (auto it = resources.begin(); it != resources.end();)
    {
        if ((*it)->loaded && it->use_count() <= 1)
        {
            unload(*it);
        }
        else
        {
            ++it;
        }
    }
}
}