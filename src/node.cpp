#include "node.h"
#include "engine.h"

const float EPSILON = 0.001;

void Node::destroy()
{
    onDestroy(*this);

    //TODO: engine->EarlyResourceReleaseCallback();
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