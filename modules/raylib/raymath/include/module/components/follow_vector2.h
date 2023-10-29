#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"

#include "module/utils.h"

namespace HeartRayLib
{
class FollowVector2 : public HeartEngine::Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(update, _on_update());
public:
    FollowVector2(std::string name,
        Vector2* follower = nullptr,
        Vector2* target = nullptr,
        Vector2 offset = {0, 0},
        bool lerp = false,
        float lerpSpeed = 10)
        : Component(name),
          follower(follower),
          target(target),
          offset(offset),
          lerp(lerp),
          lerpSpeed(lerpSpeed) {}
    FollowVector2(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Follower (Pointer)
        CHECK_ARG(1, Vector2*, follower = *result);
        // Target (Pointer)
        CHECK_ARG(1, Vector2*, target = *result);
        // Offset
        CHECK_ARG_VECTOR2(2, offset);
        // Lerp
        CHECK_ARG_BOOL(3, lerp);
        // Lerp Speed
        CHECK_ARG_FLOAT(4, lerpSpeed);
    }

    Vector2* follower = nullptr;
    Vector2* target = nullptr;

    Vector2 offset;
    bool lerp;
    float lerpSpeed;

    void _on_create() override
    {
        setupdateCall(updateCall);
    }

    void _on_update()
    {
        if (lerp)
        {
            float interpolation = lerpSpeed * node->engine->deltaTime;
            *follower = Vector2Lerp(*follower, Vector2Add(*target, offset), interpolation);
        }
        else
        {
            *follower = Vector2Add(*target, offset);
        }
    }
};
}