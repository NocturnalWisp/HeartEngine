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