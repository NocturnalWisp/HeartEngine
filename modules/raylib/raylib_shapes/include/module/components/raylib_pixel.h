#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Pixel : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(draw, _on_draw());
public:
    Pixel(std::string name,
        raylib::Vector2 position = Vector2Zero(),
        Color color = BLACK)
        : Component(name),
          position(position),
          color(color) {}
    
    Pixel(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Position
        CHECK_ARG_VECTOR2(0, position);
        // Color
        CHECK_ARG_COLOR(1, color);
    }

    raylib::Vector2 position;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);
    }

    void _on_draw()
    {
        DrawPixelV(position, color);
    }
};
}