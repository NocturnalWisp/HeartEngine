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
        CHECK_ARG(0, std::string, text = *result);
        // Position
        CHECK_ARG(1, raylib::Vector2, position = *result);
        CHECK_ARG(1, std::vector<float>, position = tableToVector2(*result));
        // Font Size
        CHECK_ARG(2, float, fontSize = *result);
        // Rotation
        CHECK_ARG(3, float, rotation = *result);

        // Color
        CHECK_ARG(4, Color, color = *result);
        // Color as int (hex)
        CHECK_ARG(4, int, color = GetColor(*result));
        // Color as vector of floats (rgba)
        CHECK_ARG(4, std::vector<float>, color = tableToColor(*result));
    }

    std::string text;
    raylib::Vector2 position;
    float fontSize;
    float rotation;
    Color color;

    void populateLuaData() override
    {
        auto type = CREATE_USER_TYPE(Label);

        type["text"] = &Label::text;
    }

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