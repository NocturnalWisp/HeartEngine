#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"

#include "module/raylib_draw_mode.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Camera2D : public Component
{
    SETUP_COMPONENT()
public:
    Camera2D(std::string name)
        : Component(name) {}
    Camera2D(std::string name, sol::variadic_args args)
        : Component(name) {}

    raylib::Camera2D camera;

    raylib::Vector2 offset;
    raylib::Vector2* target = nullptr;
    float rotation = 0;
    float zoom = 1;

    void _on_create() override
    {
        // Add to draw mode registry.
        node->engine->registerDrawMode(name,
            std::unique_ptr<DrawMode>(new DrawModeCamera2D(camera)));

        node->engine->events["update"].addListener([this]()
            { _on_update(); });
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

    raylib::Vector2 GetScreenToWorld(raylib::Vector2 position) const
    {
        return camera.GetScreenToWorld(position);
    }

    raylib::Vector2 GetWorldToScreen(raylib::Vector2 position) const
    {
        return camera.GetWorldToScreen(position);
    }
};
}