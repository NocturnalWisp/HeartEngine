#include "node.h"
#include "engine.h"

#include <algorithm>

namespace HeartEngine
{
template <> Component& Node::addComponent(Component, std::string);
template <> Component& Node::getComponentT(std::string_view) const;

Component& Node::getComponent(std::string_view name) const
{
    for (const auto &component : components)
    {
        if (component->name.compare(name) == 0)
        {
            return *component.get();
        }
    }

    throw HeartException({"No component found with name: ", name, " on node: ", this->name});
}

void Node::removeComponent(std::string_view name)
{
    //TODO
}

void Node::destroy()
{
    engine->removeNode(name);

    engine->checkEarlyResourceRelease();
}

Component& Node::addComponent(std::string_view typeName, std::string name, sol::variadic_args va)
{
    auto component = engine->findComponentInRegistry(typeName, name, va);

    if (component == nullptr)
    {
        throw HeartException({"Could not find component: ", typeName, " in the registry. Make sure to register the component with the engine before trying to use it."});
    }

    Component* componentPtr = component.get();

    components.push_back(std::move(component));

    componentPtr->node = this;
    componentPtr->setupLuaState(*luaState, "");

    return *componentPtr;
}

void Node::onCreate()
{
    for (auto &component : components)
    {
        component->_on_create();
    }
}
void Node::onDestroy()
{
    for (auto& component : components)
    {
        component->_on_destroy();
    }

    components.clear();
}

EventHandle* Node::addEventListener(std::string eventName, std::function<void()> function)
{
    return events.events[eventName].addListener(function);
}
EventHandle* Node::addEventListener(std::string eventName, std::function<void(sol::object)> function)
{
    return events.events[eventName].addListener(function);
}
EventHandle* Node::addEventListener(std::string eventName, std::function<void(sol::object, sol::object)> function)
{
    return events.events[eventName].addListener(function);
}

void Node::removeEventListener(std::string eventName, EventHandle& handle)
{
    events.events[eventName].removeListener(handle);
}

void Node::runEvent(std::string eventName)
{
    events.events[eventName].run();
}
void Node::runEvent(std::string eventName, sol::object arg1)
{
    events.events[eventName].run(arg1);
}
void Node::runEvent(std::string eventName, sol::object arg1, sol::object arg2)
{
    events.events[eventName].run(arg1, arg2);
}

void Node::deleteEvent(std::string eventName)
{
    events.events.erase(eventName);
}

void Node::setupLuaState(sol::state& p_luaState, std::string scriptName)
{
    luaState = &p_luaState;

    // Create lua environment.
    if (scriptName.compare("") != 0)
    {
        luaEnv = sol::environment(*luaState, sol::create, luaState->globals());

        populateEnvironment();

        engine->fileManager.loadScript(scriptName, *luaState, std::make_optional(luaEnv));
    }

    if (engine->started)
    {
        onCreate();
    }
}

void Node::populateEnvironment()
{
    luaEnv.set("name", &name);
    luaEnv["engine"] = engine;

    luaEnv["addComponent"] =
        [this](std::string_view typeName, std::string name, sol::variadic_args va) -> sol::table
        {
            //TODO: Breaks with error expected table recieved nil if populateLuaData is not setup.
            return addComponent(typeName, name, va).luaEnv[name];
        };
    luaEnv["addLuaComponent"] =
        [this](std::string scriptName, std::string name) -> sol::table&
        {
            return addComponent(LuaComponent(name), scriptName).luaEnv;
        };
    
    luaEnv["getComponent"] =
        [this](std::string_view component) -> sol::table&
        {
            return getComponent(component).luaEnv;
        };

    luaEnv["addEventListener"] =
        [this](std::string eventName, sol::function function) -> EventHandle*
        {
            return addEventListener(eventName, [function](sol::object obj1, sol::object obj2){ function(obj1, obj2); });
        };
    luaEnv["removeEventListener"] = &Node::removeEventListener;
    luaEnv["runEvent"] = static_cast<void(Node::*)(std::string)>(&runEvent);
    luaEnv["runEvent"] = static_cast<void(Node::*)(std::string, sol::object)>(&runEvent);
    luaEnv["runEvent"] = static_cast<void(Node::*)(std::string, sol::object, sol::object)>(&runEvent);
}
}