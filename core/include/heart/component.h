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

#define GET_COMPONENT(type, name) \
    node->getComponentT<type>(__STRINGIFY(name))

// Define the requireComponents method.
#define REQUIRE_COMPONENTS(...) protected: \
    std::vector<Component*> requireComponents() override \
    { \
        return { __VA_ARGS__ }; \
    }

// A method for changing which mode to draw to through the engine draw events.
#define DRAW_CALLABLE(drawMethod) public: \
    void SetDrawCall(std::string p_drawCall) \
    { \
        if (drawHandle != nullptr) \
        { \
            node->engine->events[drawCall].removeListener(*drawHandle); \
        } \
        drawCall = p_drawCall; \
        drawHandle = node->engine->events[drawCall].addListener([this](){ drawMethod; }); \
    } \
private: \
    std::string drawCall = "draw"; \
    const EventHandle* drawHandle = nullptr;

// Check the argument in variadic parameters and use the result if valid.
#define CHECK_ARG(index, type, statement) \
    if (auto result = checkArg<type>(args[index])) \
        statement
}