#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Circle : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(draw, _on_draw());
public:
    Circle(std::string name,
        raylib::Vector2 center = Vector2Zero(),
        float radius = 0,
        Color color = BLACK)
        : Component(name),
          center(center),
          radius(radius),
          color(color) {}
    
    Circle(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Center
        CHECK_ARG_VECTOR2(0, center);
        // Radius
        CHECK_ARG_FLOAT(1, radius);
        // Color
        CHECK_ARG_COLOR(2, color);
    }

    raylib::Vector2 center;
    float radius;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);
    }

    void _on_draw()
    {
        DrawCircleV(center, radius, color);
    }
};
}