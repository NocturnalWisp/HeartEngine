#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Triangle : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(draw, _on_draw());
public:
    Triangle(std::string name,
        raylib::Vector2 v1 = {},
        raylib::Vector2 v2 = {},
        raylib::Vector2 v3 = {},
        Color color = BLACK)
        : Component(name),
          v1(v1),
          v2(v2),
          v3(v3),
          color(color) {}
    
    Triangle(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // V1
        CHECK_ARG_VECTOR2(0, v1);
        // V2
        CHECK_ARG_VECTOR2(1, v2);
        // V3
        CHECK_ARG_VECTOR2(2, v3);
        // Color
        CHECK_ARG_COLOR(3, color);
    }

    raylib::Vector2 v1;
    raylib::Vector2 v2;
    raylib::Vector2 v3;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);
    }

    void _on_draw()
    {
        DrawTriangle(v1, v2, v3, color);
    }
};
}