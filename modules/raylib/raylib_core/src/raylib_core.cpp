#include "module/raylib_core.h"

#include <raylib-cpp.hpp>

#include "heart/engine.h"
#include "heart/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
{
    void RayLibCore::initialize(HeartEngine::Engine& engine)
    {
        SetTraceLogLevel(4);
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);
    }

    void RayLibCore::close(HeartEngine::Engine& engine)
    {
        CloseWindow();
    }

    void RayLibCore::startDraw(HeartEngine::Engine& engine)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
    }

    void RayLibCore::endDraw(HeartEngine::Engine& engine)
    {
        EndDrawing();

        SwapScreenBuffer();

        engine.shouldCloseWindow = WindowShouldClose();
    }
}