#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Label : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(draw, _on_draw());
public:
    Label(std::string name, std::string text = "",
        Rectangle rect = {0, 0, 100, 100},
        bool bestFit = false,
        float fontSize = 10,
        Vector2 anchor = {0, 0},
        float rotation = 0,
        Color color = BLACK)
        : Component(name),
          text(text),
          rect(rect),
          bestFit(bestFit),
          fontSize(fontSize),
          anchor(anchor),
          rotation(rotation),
          color(color) {}
    
    Label(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Text
        CHECK_ARG_STRING(0, text);
        // Rect
        CHECK_ARG_RECT(1, rect);
        // Best Fit
        CHECK_ARG_BOOL(2, bestFit);
        // Font Size
        CHECK_ARG_FLOAT(3, fontSize);
        // Anchor
        CHECK_ARG_VECTOR2(4, anchor);
        // Rotation
        CHECK_ARG_FLOAT(5, rotation);
        // Color
        CHECK_ARG_COLOR(6, color);
    }

    std::string text = "";
    Rectangle rect = {0, 0, 100, 100};
    bool bestFit = false;
    float fontSize = 10;
    Vector2 anchor = {0, 0};
    float rotation = 0;
    Color color = BLACK;

    void _on_create() override
    {
        setdrawCall(drawCall);
    }

    void _on_draw()
    {
        Vector2 rectSize = {rect.width, rect.height};

        Vector2 defaultSize = MeasureTextEx(GetFontDefault(), text.c_str(), 1, 0.1);

        Vector2 measuredSize = Vector2Divide(rectSize, defaultSize);

        float newFontSize = measuredSize.x < measuredSize.y ? measuredSize.x : measuredSize.y;

        DrawTextPro(
            GetFontDefault(),
            text.c_str(),
            // rect.position + (anchor * rect.size)
            Vector2Add({rect.x, rect.y}, Vector2Multiply(anchor, rectSize)),
            Vector2Multiply(anchor, Vector2Scale(defaultSize, newFontSize)),
            rotation,
            newFontSize,
            newFontSize / 10,
            color);
    }
};
}