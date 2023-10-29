#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"

#include "module/raylib_draw_mode.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Camera2DComponent : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(update, _on_update());
public:
    Camera2DComponent(std::string name)
        : Component(name) {}
    Camera2DComponent(std::string name, sol::variadic_args args)
        : Component(name) {}

    Camera2D camera;

    Vector2 offset;
    Vector2* target = nullptr;
    float rotation = 0;
    float zoom = 1;

    void _on_create() override
    {
        // Add to draw mode registry.
        node->engine->registerDrawMode(name,
            std::unique_ptr<DrawMode>(new DrawModeCamera2D(camera)));

        setupdateCall(updateCall);
    }

    void _on_destroy() override
    {
        // Remove from draw mode registry.
        node->engine->unregisterDrawMode(name);
    }

    void _on_update()
    {
        camera.offset = offset;
        camera.target = target != nullptr ? *target : Vector2Zero();
        camera.rotation = rotation;
        camera.zoom = zoom;
    }

    Vector2 GetScreenToWorld(Vector2 position) const
    {
        return GetScreenToWorld2D(position, camera);
    }

    Vector2 GetWorldToScreen(Vector2 position) const
    {
        return GetWorldToScreen2D(position, camera);
    }
};
}