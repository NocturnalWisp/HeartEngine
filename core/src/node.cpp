#include "node.h"
#include "engine.h"

#include <algorithm>

const float EPSILON = 0.001;

Component* Node::getComponent(std::string_view name) const
{
    Component *foundComponent;

    for (const auto &component : components)
    {
        if (component->name.compare(name) == 0)
        {
            foundComponent = component.get();
        }
    }

    return foundComponent;
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

Component* Node::addComponent(std::string_view typeName, std::string name)
{
    auto component = engine->getComponentFromRegistry(typeName, name);

    if (component != nullptr)
    {
        component->node = this;

        auto ptr = component.get();

        components.push_back(std::move(component));

        return ptr;
    }

    return nullptr;
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