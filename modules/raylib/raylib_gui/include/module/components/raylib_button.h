#pragma once

#include <raylib-cpp.hpp>

#include "module/raylib_gui.h"

#include "heart/engine.h"
#include "heart/utils.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Button : public Component
{
    EVENT_CALLABLE(draw, _on_draw());
public:
    Button(std::string name,
        raylib::Rectangle rect = {},
        raylib::Vector2 origin = Vector2Zero(),
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
        CHECK_ARG(0, raylib::Rectangle, rect = *result);
        CHECK_ARG(0, std::vector<float>, rect = tableToRectangle(*result));
        // origin
        CHECK_ARG(1, raylib::Vector2, origin = *result);
        CHECK_ARG(1, std::vector<float>, origin = tableToVector2(*result));
        // Rotation
        CHECK_ARG(2, float, rotation = *result);

        // Color
        CHECK_ARG(3, Color, color = *result);
        // Color as int (hex)
        CHECK_ARG(3, int, color = GetColor(*result));
        // Color as vector of floats (rgba)
        CHECK_ARG(3, std::vector<float>, color = tableToColor(*result));
    }

    raylib::Rectangle rect;
    raylib::Vector2 origin;
    float rotation;
    Color color;

    void _on_create() override
    {
        setdrawCall(drawCall);

        node->engine->events["input"]["mouse"]["left"]["released"].addListener([this]() {_on_mouse_click();});
    }

    void _on_draw()
    {
        DrawRectanglePro(rect, origin, rotation, color);
    }

    void _on_mouse_click()
    {
        // NOTE: Will not currently properly check if the button is rotated.
        //  Need to implement some kind of AABB I guess.
        if (CheckCollisionPointRec(GetMousePosition(), rect))
        {
            node->events[name]["pressed"].run();
        }
    }
};
}