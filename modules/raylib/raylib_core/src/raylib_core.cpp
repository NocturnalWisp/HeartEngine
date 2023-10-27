#include "module/raylib_core.h"

#include "heart/engine.h"
#include "heart/utils.h"

#include "module/components/camera2d.h"

using namespace HeartEngine;

namespace HeartRayLib
{
    void RayLibCore::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
    {
        //TODO: Move camera to its own module.
        auto camera2dType = REGISTER_COMPONENT(Camera2D);

        ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, GetScreenToWorld);
        ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, GetWorldToScreen);

        ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, offset);
        ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, target);
        ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, rotation);
        ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, zoom);
    }

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