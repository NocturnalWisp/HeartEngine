#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/utils.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Line : public Component
{
    EVENT_CALLABLE(draw, _on_draw());
public:
    Line(std::string name,
        raylib::Vector2 start = Vector2Zero(),
        raylib::Vector2 end = Vector2Zero(),
        float thickness = 0,
        Color color = BLACK)
        : Component(name),
          start(start),
          end(end),
          thickness(thickness),
          color(color) {}
    
    Line(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Start
        CHECK_ARG_VECTOR2(0, start);
        // End
        CHECK_ARG_VECTOR2(1, end);
        // Thickness
        CHECK_ARG_FLOAT(2, thickness);
        // Color
        CHECK_ARG_COLOR(3, color);
    }

    raylib::Vector2 start;
    raylib::Vector2 end;
    float thickness;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);
    }

    void _on_draw()
    {
        DrawLineEx(start, end, thickness, color);
    }
};
}