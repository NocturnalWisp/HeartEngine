#include "engine.h"

#include <algorithm>
#include <functional>

namespace HeartEngine
{
Engine::Engine()
{
    lua = std::make_unique<sol::state>(sol::state());
    lua->open_libraries(sol::lib::base);

    populateBasicLua();
}

void Engine::init()
{
    started = true;

    // Initialize modules.
    for (auto& mod : moduleRegistry)
        mod->initialize(*this);

    // Creation
    for (auto& node : nodes)
        node->onCreate();

    if (checkResourceRelease)
        checkEarlyResourceRelease();
}

void Engine::run()
{
    double previousTime = getTime();
    double lag = 0.0;

    while (!shouldCloseWindow)
    {
        // Update
        double currentTime = getTime();
        deltaTime = currentTime - previousTime;

        for (auto& mod : moduleRegistry)
            mod->beforeUpdate(*this);

        // Variable update loop.
        events["update"].run();

        for (auto& mod : moduleRegistry)
            mod->afterUpdate(*this);

        previousTime = currentTime;

        lag += deltaTime;

        // Fixed update loop.
        while (lag >= fixedDeltaTime)
        {
            for (auto& mod : moduleRegistry)
                mod->beforeFixedUpdate(*this);

            events["fixed_update"].run();
            lag -= fixedDeltaTime;

            for (auto& mod : moduleRegistry)
                mod->afterFixedUpdate(*this);
        }

        // Drawing Start
        for (auto& mod : moduleRegistry)
            mod->startDraw(*this);

        // Draw modes.
        for (auto& drawMode : drawModeRegistry)
        {
            drawMode.second->startMode();

            events["draw"][drawMode.first].runAll();

            drawMode.second->endMode();
        }

        // Draw anything outside a mode overtop.
        events["draw"].run();

        for (auto& mod : moduleRegistry)
            mod->endDraw(*this);

        // Handle hanging resources
        //TODO: Iterating on the list every loop is especially unessecary.
        if (checkResourceRelease)
            checkEarlyResourceRelease();
    }

    // Destruction
    for (auto& node : nodes)
        node->onDestroy();

    for (auto& res : resources)
        unload(res);

    for (auto& mod : moduleRegistry)
        mod->close(*this);
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

// Resource handling.
Resource& Engine::loadResource(std::string_view typeName, std::string name, sol::variadic_args args)
{
    auto resource = getResourceFromRegistry(typeName, name, args);

    if (resource == nullptr)
    {
        throw HeartException({"Could not find resource: ", typeName, " in the registry. Make sure to register both the module AND the resource with the engine."});
    }

    Resource* resPtr = resource.get();

    resources.push_back(std::move(resource));

    resPtr->engine = this;
    resPtr->setupLuaState(*lua, "");

    return *resPtr;
}

std::shared_ptr<Resource> Engine::getResource(std::string_view name) const
{
    for (const auto &res : resources)
    {
        if (res->name.compare(name) == 0)
        {
            return res;
        }
    }

    throw HeartException({"No resource found with name: ", name, "."});
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
    // Events
    auto eventManagerType = lua->new_usertype<EventManager>("EventManager");

    ADD_LUA_FUNCTION_W_TYPE(eventManagerType, EventManager, addEvent);
    ADD_LUA_FUNCTION_W_TYPE(eventManagerType, EventManager, deleteEvent);
    ADD_LUA_FUNCTION_W_TYPE(eventManagerType, EventManager, getSubBus);

    eventManagerType[sol::meta_function::index] = &EventManager::operator[];

    auto eventBusType = lua->new_usertype<EventBus>("EventBus");

    eventBusType["addListener"] = [](EventBus& self, sol::function function) -> const EventHandle*
        {
            return self.addListener(function);
        };
    ADD_LUA_FUNCTION_W_TYPE(eventBusType, EventBus, removeListener);
    ADD_LUA_FUNCTION_W_TYPE(eventBusType, EventBus, run);
    ADD_LUA_FUNCTION_W_TYPE(eventBusType, EventBus, runAll);

    ADD_LUA_FUNCTION_W_TYPE(eventBusType, EventBus, addSubEvent);
    ADD_LUA_FUNCTION_W_TYPE(eventBusType, EventBus, deleteSubEvent);

    eventBusType[sol::meta_function::index] = &EventBus::operator[];
    ADD_LUA_FUNCTION_W_TYPE(eventBusType, EventBus, recursiveGetSubBus);

    // Engine
    auto engineType = lua->new_usertype<Engine>("Engine");

    engineType["loadResource"] = 
        [](Engine& self, std::string typeName, std::string name, sol::variadic_args va) -> sol::table
        {
            return self.loadResource(typeName, name, va).luaEnv[name];
        };
    engineType["loadLuaResource"] = 
        [](Engine& self, std::string scriptName, std::string name) -> sol::table&
        {
            return self.loadResource(LuaResource(name), scriptName)->luaEnv;
        };
    engineType["getResource"] = &Engine::getResource;

    engineType["getNode"] = &Engine::getNode;

    engineType["addContainer"] = sol::overload(
        [](Engine& self, std::string name) -> Node*
            { return self.addNode<Container>(name); },
        [](Engine& self, std::string name, Container* container) -> Node*
            { return self.addNode<Container>(name, container); });

    engineType["addNode"] = sol::overload(
        [](Engine& self, std::string name) -> Node*
            { return self.addNode<Node>(name); },
        [](Engine& self, std::string name, Container* container) -> Node*
            { return self.addNode<Node>(name, container); });

    engineType["addLuaNode"] = sol::overload(
        [](Engine& self, std::string scriptName, std::string name) -> Node*
            { return self.addNode<Node>(name, nullptr, scriptName); },
        [](Engine& self, std::string scriptName, std::string name, Container* container) -> Node*
            { return self.addNode<Node>(name, container, scriptName); });

    engineType["removeNode"] = &Engine::removeNode;
    engineType["events"] = &Engine::events;

    // Node
    auto nodeType = lua->new_usertype<Node>("Node");

    nodeType["name"] = &Node::name;
    nodeType["addComponent"] =
        [](Node& self, std::string_view typeName, std::string name, sol::variadic_args va) -> sol::table
        {
            return self.addComponent(typeName, name, va).luaEnv[name];
        },
    nodeType["addLuaComponent"] =
        [](Node& self, std::string scriptName, std::string name) -> sol::table&
        {
            return self.addComponent(LuaComponent(name), scriptName)->luaEnv;
        };
    nodeType["getComponent"] =
        [](Node& self, std::string_view component) -> sol::table
        {
            auto foundComponent = &self.getComponent(component);
            if (foundComponent->isLuaScript)
            {
                return foundComponent->luaEnv;
            }
            else
            {
                return foundComponent->luaEnv[component];
            }
        };

    //TODO: remove component should remove any table usage.
    // nodeType["removeComponent"] = &Node::removeComponent;
    nodeType["engine"] = &Node::engine;

    nodeType["events"] = &Node::events;
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

std::shared_ptr<Resource> Engine::getResourceFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va)
{
    for (const auto &resourceType : resourceRegistry)
    {
        if (resourceType.first.compare(typeName) == 0)
        {
            return resourceType.second(name, va);
        }
    }

    return nullptr;
}

void Engine::registerDrawMode(std::string name, std::unique_ptr<DrawMode> drawMode)
{
    drawModeRegistry[name] = std::move(drawMode);
}

void Engine::unregisterDrawMode(std::string name)
{
    drawModeRegistry.erase(name);
}
}