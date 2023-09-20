#include "engine.h"

#include <algorithm>
#include <functional>

#include <raylib.h>
#include <raymath.h>

#include <sol.hpp>

#include "lua_wrappers/lua_node.h"

Engine::Engine()
{
    SetTraceLogLevel(4);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);

    return ;
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

template <> Node* Engine::addNode(Node n);
template <> LuaNode* Engine::addNode(LuaNode n);

std::unique_ptr<Component> Engine::getComponentFromRegistry(std::string_view typeName, std::string name)
{
    for (const auto &componentType : componentRegistry)
    {
        if (componentType.first.compare(typeName) == 0)
        {
            return componentType.second(name);
        }
    }

    return nullptr;
}

void Engine::registerComponent(std::string typeName, std::unique_ptr<Component>(*creator)(std::string name))
{
    componentRegistry[typeName] = creator;
}

void Engine::populateBasicLua(sol::state& lua)
{
    // Event System
    lua.new_usertype<EventHandle>("EventHandle");

    // Engine
    lua.new_usertype<Engine>("Engine",
        "getNode", &Engine::getNode,
        "addNode", [](Engine& self, std::string name) -> Node*
            { return self.addNode<Node>(Node(name)); },
        "addLuaNode", [](Engine& self, std::string scriptName) -> Node*
            { return self.addNode<Node>(LuaNode(scriptName)); },
        "removeNode", &Engine::removeNode
    );

    // Node
    lua.new_usertype<Node>("Node",
        "name", &Node::name,
        "getComponent", &Node::getComponent,
        "addComponent", [](Node& self, std::string_view typeName, std::string name, sol::table args) -> Component*
            { return self.addComponent(typeName, name); },
        "removeComponent", &Node::removeComponent,
        "engine", &Node::engine,

        "addEventListener", [](Node& self, std::string eventName, sol::function function) -> EventHandle*
            {
                return self.addEventListener(eventName, [function](sol::object obj1, sol::object obj2){ function(obj1, obj2); });
            },
        "runEvent", static_cast<void(Node::*)(std::string)>(&Node::runEvent),
        "runEvent", static_cast<void(Node::*)(std::string, sol::object)>(&Node::runEvent),
        "runEvent", static_cast<void(Node::*)(std::string, sol::object, sol::object)>(&Node::runEvent)
    );

    // Component
    lua.new_usertype<Component>("Component",
        "name", &Component::name,
        "node", &Component::node
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