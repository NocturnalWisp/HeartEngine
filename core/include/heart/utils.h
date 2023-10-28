#pragma once

namespace HeartEngine
{
#define CAT_I_2(a, b) a##b
#define CAT2(a, b) CAT_I_2(a, b)
#define CAT_I_3(a, b, c) a##b##c
#define CAT3(a, b, c) CAT_I_3(a, b, c)

// Modules

#define ADD_LUA_FUNCTION(table, name) table[__STRINGIFY(name)] = &name
#define ADD_LUA_FUNCTION_W_TYPE(table, type, name) table[__STRINGIFY(name)] = &type::name

#define ADD_LUA_COPY(table, name) table[__STRINGIFY(name)] = name

// Components

#define GET_COMPONENT(type, name) \
    node->getComponentT<type>(__STRINGIFY(name))

// Define the requireComponents method.
#define REQUIRE_COMPONENTS(...) protected: \
    std::vector<HeartEngine::Component*> requireComponents() override \
    { \
        return { __VA_ARGS__ }; \
    }

// A method for changing which event to listen to externally from the class.
#define EVENT_CALLABLE(eventName, callMethod) public: \
    void CAT3(set, eventName, Call) (HeartEngine::EventBus* p_Call) \
    { \
        if (CAT2(eventName, Handle) != nullptr) \
        { \
            CAT2(eventName, Call)->removeListener(*CAT2(eventName, Handle)); \
        } \
        if (CAT2(eventName, Call) == nullptr) \
        { \
            /* Initialize to a top engine event called eventName if null previously. */ \
            CAT2(eventName, Call) = &node->engine->events[__STRINGIFY(eventName)]; \
        } \
        else \
        { \
            CAT2(eventName, Call) = p_Call; \
        } \
        if (CAT2(eventName, Call) != nullptr) \
        { \
            CAT2(eventName, Handle) = CAT2(eventName, Call)->addListener([this](){ callMethod; }); \
        } \
        else \
        { \
            throw HeartEngine::HeartException({"Invalid event bus passed to CAT3(set, eventName, Call)."}); \
        } \
    } \
private: \
    HeartEngine::EventBus* CAT2(eventName, Call) = nullptr; \
    const HeartEngine::EventHandle* CAT2(eventName, Handle) = nullptr

// Check the argument in variadic parameters and use the result if valid.
#define CHECK_ARG(index, type, statement) \
    if (auto result = checkArg<type>(args[index])) \
        statement

// Check arg sub macros.

#define CHECK_ARG_STRING(index, var) \
    CHECK_ARG(index, std::string, var = *result)

#define CHECK_ARG_FLOAT(index, var) \
    CHECK_ARG(index, float, var = *result)

#define CHECK_ARG_INT(index, var) \
    CHECK_ARG(index, int, var = *result)

#define CHECK_ARG_BOOL(index, var) \
    CHECK_ARG(index, bool, var = *result)

// Simpler macro to register a component to the engine lua state.
#define REGISTER_COMPONENT(type) \
    engine.registerComponent<type>(__STRINGIFY(type), &HeartEngine::Engine::componentBuilder<type>)
}