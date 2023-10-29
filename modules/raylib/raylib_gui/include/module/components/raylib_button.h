#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Button : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(draw, _on_draw());
    EVENT_CALLABLE(update, _on_update());
public:
    Button(std::string name,
        Rectangle rect = {},
        Vector2 origin = Vector2Zero(),
        float rotation = 0,
        Color color = BLACK)
        : Component(name),
          rect(rect),
          origin(origin),
          rotation(rotation),
          color(color) {}
    
    Button(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Rect
        CHECK_ARG_RECT(0, rect);
        // origin
        CHECK_ARG_VECTOR2(1, origin);
        // Rotation
        CHECK_ARG_FLOAT(2, rotation);
        // Color
        CHECK_ARG_COLOR(3, color);
    }

    Rectangle rect;
    Vector2 origin;
    float rotation;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);
        setupdateCall(updateCall);
    }

    void _on_draw()
    {
        DrawRectanglePro(rect, origin, rotation, color);
    }

    void _on_update()
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            // NOTE: Will not currently properly check if the button is rotated.
            //  Need to implement some kind of AABB I guess.
            if (CheckCollisionPointRec(GetMousePosition(), rect))
            {
                node->events[name]["pressed"].run();
            }
        }
    }
};
}