#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include "heart/module.h"

#include "heart/engine.h"
#include "heart/debug.h"

namespace HeartEngine { class Engine; }

namespace HeartRayLib
{
constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class RayLibCore : public HeartEngine::Module
{
public:
    RayLibCore(bool includeCamera = true,
            bool includeWindow = false,
            bool includeMonitor = false,
            bool includeCursor = false)
        : includeCamera(includeCamera),
          includeWindow(includeWindow),
          includeMonitor(includeMonitor),
          includeCursor(includeCursor) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        SetTraceLogLevel(4);
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);

        if (includeCamera)
            SetupCamera(engine, lua);
        if (includeWindow)
            SetupWindow(engine, lua);
        if (includeMonitor)
            SetupMonitor(engine, lua);
        if (includeCursor)
            SetupCursor(engine, lua);
    }

    void duringUpdate(HeartEngine::Engine& engine) override
    {
        PollInputEvents();

        handleInputEvents(engine);
    }
    void closeApplication(HeartEngine::Engine& engine) override
    {
        CloseWindow();
    }

    void startDraw(HeartEngine::Engine& engine) override
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
    }
    void endDraw(HeartEngine::Engine& engine)
    {
        EndDrawing();

        SwapScreenBuffer();

        engine.shouldCloseWindow = WindowShouldClose();
    }

    void SetupCamera(HeartEngine::Engine& engine, sol::state& lua);
    void SetupWindow(HeartEngine::Engine& engine, sol::state& lua);
    void SetupMonitor(HeartEngine::Engine& engine, sol::state& lua);
    void SetupCursor(HeartEngine::Engine& engine, sol::state& lua);
private:
    void handleInputEvents(HeartEngine::Engine& engine);

    bool includeCamera;
    bool includeWindow;
    bool includeMonitor;
    bool includeCursor;
};
}