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
    RayLibCore(bool includeWindow = false,
            bool includeMonitor = false,
            bool includeCursor = false,
            bool includeTiming = true)
        : includeWindow(includeWindow),
        includeMonitor(includeMonitor),
        includeCursor(includeCursor),
        includeTiming(includeTiming) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        SetTraceLogLevel(4);
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);

        if (includeWindow)
            SetupWindow(engine, lua);
        if (includeMonitor)
            SetupMonitor(engine, lua);
        if (includeCursor)
            SetupCursor(engine, lua);
        if (includeTiming)
            SetupTiming(engine, lua);
    }

    void duringUpdate(HeartEngine::Engine& engine) override
    {
        engine.shouldCloseWindow = WindowShouldClose();
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
    }

    void SetupWindow(HeartEngine::Engine& engine, sol::state& lua);
    void SetupMonitor(HeartEngine::Engine& engine, sol::state& lua);
    void SetupCursor(HeartEngine::Engine& engine, sol::state& lua);
    void SetupTiming(HeartEngine::Engine& engine, sol::state& lua);
private:
    bool includeWindow;
    bool includeMonitor;
    bool includeCursor;
    bool includeTiming;
};
}