#include "module/raylib_camera.h"

#include "heart/engine.h"

#include "module/components/camera2d.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibCamera::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    auto camera2dType = REGISTER_COMPONENT(Camera2D);

    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, GetScreenToWorld);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, GetWorldToScreen);

    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, offset);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, target);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, rotation);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2D, zoom);
}
}