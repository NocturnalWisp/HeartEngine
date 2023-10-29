#include "module/raylib_camera.h"

#include "heart/engine.h"

#include "module/components/camera2d.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibCamera::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    auto camera2dType = REGISTER_COMPONENT(Camera2DComponent);

    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2DComponent, GetScreenToWorld);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2DComponent, GetWorldToScreen);

    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2DComponent, offset);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2DComponent, target);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2DComponent, rotation);
    ADD_LUA_FUNCTION_W_TYPE(camera2dType, Camera2DComponent, zoom);
}
}