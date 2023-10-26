#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/utils.h"
#include "heart/node.h"
#include "heart/component.h"

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
    Label(std::string name, sol::variadic_args args);

    std::string text;
    raylib::Vector2 position;
    float fontSize;
    float rotation;
    Color color;

    void populateLuaData() override;

    void _on_create() override;

    void _on_draw();
};
}