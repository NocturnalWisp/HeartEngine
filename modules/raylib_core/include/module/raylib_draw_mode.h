#pragma once

#include <raylib-cpp.hpp>

#include "heart/draw_mode.h"

namespace HeartModules
{
class DrawModeCamera2D : public DrawMode
{
public:
    DrawModeCamera2D(raylib::Camera2D& camera)
        : camera(&camera) {}

    raylib::Camera2D* camera;

    void startMode() override
    {
        camera->BeginMode();
    }

    void endMode() override
    {
        camera->EndMode();
    }
};
}