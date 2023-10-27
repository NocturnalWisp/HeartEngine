#include "module/raylib_core.h"

#include "heart/engine.h"
#include "heart/utils.h"

using namespace HeartEngine;

namespace HeartRayLib
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

//TODO: Move to heart raylib input.
void RayLibCore::handleInputEvents(HeartEngine::Engine& engine)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        engine.events["input"]["mouse"]["left"]["pressed"].run();
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        engine.events["input"]["mouse"]["left"]["released"].run();

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        engine.events["input"]["mouse"]["right"]["pressed"].run();
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        engine.events["input"]["mouse"]["right"]["released"].run();
    
    auto key = GetKeyPressed();
    while (key != 0)
    {
        engine.events["input"]["keyboard"][std::to_string(key)].run();
    }
}
}