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
class Label : public Component
{
    EVENT_CALLABLE(draw, _on_draw());
public:
    Label(std::string name, std::string text = "",
        raylib::Vector2 position = Vector2Zero(),
        float fontSize = 10,
        float rotation = 0,
        Color color = BLACK)
        : Component(name),
          text(text),
          position(position),
          fontSize(fontSize),
          rotation(rotation),
          color(color) {}
    
    Label(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Text
        CHECK_ARG_STRING(0, text);
        // Position
        CHECK_ARG_VECTOR2(1, position);
        // Font Size
        CHECK_ARG_FLOAT(2, fontSize);
        // Rotation
        CHECK_ARG_FLOAT(3, rotation);
        // Color
        CHECK_ARG_COLOR(4, color);
    }

    std::string text;
    raylib::Vector2 position;
    float fontSize;
    float rotation;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);
    }

    void _on_draw()
    {
        raylib::DrawTextPro(
            GetFontDefault(),
            text.c_str(),
            position,
            Vector2Zero(),
            rotation,
            fontSize,
            fontSize / 10,
            color);
    }
};
}