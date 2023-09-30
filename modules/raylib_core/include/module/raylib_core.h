#pragma once

#include <sol/sol.hpp>
#include <raylib-cpp.hpp>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartModules
{
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
        if (includeWindow)
            SetupWindow(engine, lua);
        if (includeMonitor)
            SetupMonitor(engine, lua);
        if (includeCursor)
            SetupCursor(engine, lua);
        if (includeTiming)
            SetupTiming(engine, lua);
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