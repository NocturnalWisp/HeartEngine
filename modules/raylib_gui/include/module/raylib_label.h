#pragma once

#include <raylib-cpp.hpp>

#include "heart/component.h"

#include "module/transform_3d.h"

using namespace HeartEngine;

namespace HeartModules
{
class Label : public Component
{
protected:
    HeartModules::Transform3D* transform;
public:
    Label(std::string name) : Component(name) {}
    Label(std::string name, std::string text) : Component(name), text(text) {}

    std::string text;

    void populateLuaData() override;

    void _on_create() override;

    void _on_draw();
};
}