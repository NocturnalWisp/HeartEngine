#include "module/raylib_core.h"

#include "heart/engine.h"

using namespace HeartEngine;

namespace HeartModules
{
void RayLibCore::SetupWindow(HeartEngine::Engine& engine, sol::state& lua)
{
    //TODO:
}
void RayLibCore::SetupMonitor(HeartEngine::Engine& engine, sol::state& lua)
{
    //TODO:
}
void RayLibCore::SetupCursor(HeartEngine::Engine& engine, sol::state& lua)
{
    //TODO:
}
void RayLibCore::SetupTiming(Engine& engine, sol::state& lua)
{
    auto rayLibType = lua.create_named_table("RayLib");

    ADD_LUA_FUNCTION(rayLibType, WaitTime);
    ADD_LUA_FUNCTION(rayLibType, SetTargetFPS);
    ADD_LUA_FUNCTION(rayLibType, GetFPS);
    ADD_LUA_FUNCTION(rayLibType, GetFrameTime);
    ADD_LUA_FUNCTION(rayLibType, GetTime);
}
}