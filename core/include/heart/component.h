#pragma once

#include <string>
#include <optional>

#include <sol/sol.hpp>

#include "debug.h"

#include "event.h"

#include "lua_environment.h"

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

    virtual void populateLuaData() override = 0;

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
public:
    LuaComponent(std::string name) : Component(name) {}

    void populateLuaData() override {}

    //TODO: Allow setting a variable in the lua code to require components before _on_create.
    std::vector<Component*> requireComponents() override
    {
        return {};
    }
};

#define CAT_I_2(a, b) a##b
#define CAT2(a, b) CAT_I_2(a, b)
#define CAT_I_3(a, b, c) a##b##c
#define CAT3(a, b, c) CAT_I_3(a, b, c)

#define GET_COMPONENT(type, name) \
    node->getComponentT<type>(__STRINGIFY(name))

// Define the requireComponents method.
#define REQUIRE_COMPONENTS(...) protected: \
    std::vector<Component*> requireComponents() override \
    { \
        return { __VA_ARGS__ }; \
    }

// A method for changing which mode to draw to through the engine draw events.
#define EVENT_CALLABLE(eventName, callMethod) public: \
    void CAT3(set, eventName, Call) (std::vector<std::string> p_Call) \
    { \
        if (CAT2(eventName, Handle) != nullptr) \
        { \
            node->engine->events.getSubBus(CAT2(eventName, Call)).removeListener(*CAT2(eventName, Handle)); \
        } \
        CAT2(eventName, Call).clear(); \
        CAT2(eventName, Call) = p_Call; \
        CAT2(eventName, Handle) = node->engine->events.getSubBus(CAT2(eventName, Call)).addListener([this](){ callMethod; }); \
    } \
private: \
    std::vector<std::string> CAT2(eventName, Call) = {"draw"}; \
    const EventHandle* CAT2(eventName, Handle) = nullptr;

// Check the argument in variadic parameters and use the result if valid.
#define CHECK_ARG(index, type, statement) \
    if (auto result = checkArg<type>(args[index])) \
        statement
}