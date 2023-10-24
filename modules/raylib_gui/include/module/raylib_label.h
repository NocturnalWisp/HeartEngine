#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/transform_3d.h"

using namespace HeartEngine;

namespace HeartModules
{
class Label : public Component
{
    REQUIRE_COMPONENTS(transform)

    DRAW_CALLABLE(_on_draw())
public:
    Label(std::string name, std::string text = "")
        : Component(name), text(text) {}
    Label(std::string name, sol::variadic_args args);

    HeartModules::Transform3D* transform = nullptr;

    std::string text;

    void populateLuaData() override;

    void _on_create() override;

    void _on_draw();
};
}