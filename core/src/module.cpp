#include "module.h"

namespace HeartEngine
{
void Module::registerComponent(std::string typeName, std::unique_ptr<Component>(*creator)(std::string, sol::variadic_args))
{
    componentRegistry[typeName] = creator;
}

std::unique_ptr<Component> Module::getComponentFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va)
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
}