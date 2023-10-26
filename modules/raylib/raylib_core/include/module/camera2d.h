#pragma once

#include <raylib-cpp.hpp>

#include "heart/component.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class RayLibCamera2D : public Component
{
public:
    RayLibCamera2D(std::string name)
        : Component(name) {}
    RayLibCamera2D(std::string name, sol::variadic_args args)
        : Component(name) {}

    raylib::Camera2D camera;

    raylib::Vector2 offset;
    raylib::Vector2* target = nullptr;
    float rotation = 0;
    float zoom = 1;

    void populateLuaData() override;

    void _on_create() override;
    void _on_destroy() override;

    void _on_update();

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