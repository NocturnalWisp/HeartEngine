#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

using namespace HeartEngine;

namespace HeartModules
{
class Label : public Component
{
    DRAW_CALLABLE(_on_draw())
public:
    Label(std::string name, std::string text = "",
        Vector2 position = Vector2Zero(), float fontSize = 10, Color color = BLACK)
        : Component(name),
          text(text), position(position), fontSize(fontSize), color(color) {}
    Label(std::string name, sol::variadic_args args);

    std::string text;
    Vector2 position;
    float fontSize;
    Color color;

    void populateLuaData() override;

    void _on_create() override;

    void _on_draw();
};
}