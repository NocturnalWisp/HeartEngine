#pragma once

#include <string>
#include <optional>

#include <sol/sol.hpp>

#include "debug.h"

#include "event.h"

#include "lua_environment.h"

#include "heart/utils.h"

namespace HeartEngine
{
class Engine;
class Node;

class Component : public LuaEnvironment
{
    friend class Engine;
    friend class Node;
public:
    Component(std::string name) : name(name) {}

    Node* node;

    std::string name;

    virtual void _on_create();
    virtual void _on_destroy();
protected:
    template <class T>
    std::optional<T> checkArg(sol::stack_proxy arg, bool throwError = true)
    {
        if (arg.is<T>())
        {
            return arg.as<T>();
        }
        else
        {
            if (throwError)
            {
                throw HeartException({"Invalid argument passed to component: ", name, " constructor."});
            }
            return std::nullopt;
        }
    }

    virtual std::vector<Component*> requireComponents()
    {
        return {};
    }
protected:
    virtual void setEnvironment() = 0;
private:
    void setupLuaState(sol::state& state, std::string scriptName = "") override;
    void populateEnvironment() override;

    bool checkHasRequired()
    {
        for (const auto& required : requireComponents())
        {
            if (required == nullptr)
            {
                return false;
            }
        }

        return true;
    }

    bool isLuaScript = false;
};

class LuaComponent : public Component
{
    SETUP_COMPONENT();
public:
    LuaComponent(std::string name) : Component(name) {}

    //TODO: Allow setting a variable in the lua code to require components before _on_create.
    std::vector<Component*> requireComponents() override
    {
        return {};
    }
};
}