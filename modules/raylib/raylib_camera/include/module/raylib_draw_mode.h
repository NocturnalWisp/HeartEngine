#pragma once

#include <raylib-cpp.hpp>

#include "heart/draw_mode.h"

namespace HeartRayLib
{
class DrawModeCamera2D : public HeartEngine::DrawMode
{
public:
    DrawModeCamera2D(Camera2D& camera)
        : camera(&camera) {}

    Camera2D* camera;

    void startMode() override
    {
        BeginMode2D(*camera);
    }

    void endMode() override
    {
        EndMode2D();
    }
};
}