#pragma once

#include <string>

#include <sol/sol.hpp>

#include "component.h"

namespace HeartEngine
{
#define ADD_LUA_FUNCTION(table, name) table[__STRINGIFY(name)] = &name

class Engine;

class Module
{
public:
    virtual void registerTypes(sol::state& lua) {}

    // Component Registry
    template <class T>
    static std::unique_ptr<Component> componentBuilder(std::string name, sol::variadic_args va)
    {
        static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component.");
        return std::make_unique<T>(T(name, va));
    }

    void registerComponent(std::string typeName, std::unique_ptr<Component>(*creator)(std::string, sol::variadic_args));

    std::unique_ptr<Component> getComponentFromRegistry(std::string_view typeName, std::string name, sol::variadic_args va);
private:
    std::map<std::string, std::unique_ptr<Component>(*)(std::string name, sol::variadic_args va)> componentRegistry;
};
}