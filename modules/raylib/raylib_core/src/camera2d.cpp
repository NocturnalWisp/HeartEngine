#include "module/camera2d.h"

#include "heart/engine.h"

#include "module/raylib_draw_mode.h"

namespace HeartModules
{
void RayLibCamera2D::populateLuaData()
{
    auto type = luaState->new_usertype<RayLibCamera2D>("Camera2D");
    luaEnv[name] = this;

    ADD_LUA_FUNCTION_W_TYPE(type, RayLibCamera2D, GetScreenToWorld);
    ADD_LUA_FUNCTION_W_TYPE(type, RayLibCamera2D, GetWorldToScreen);

    ADD_LUA_FUNCTION_W_TYPE(type, RayLibCamera2D, offset);
    ADD_LUA_FUNCTION_W_TYPE(type, RayLibCamera2D, target);
    ADD_LUA_FUNCTION_W_TYPE(type, RayLibCamera2D, rotation);
    ADD_LUA_FUNCTION_W_TYPE(type, RayLibCamera2D, zoom);
}

void RayLibCamera2D::_on_create()
{
    // Add to draw mode registry.
    node->engine->registerDrawMode(name,
        std::make_unique<DrawModeCamera2D>(DrawModeCamera2D(camera)));

    node->engine->events["update"].addListener([this](){_on_update(); });
}

void RayLibCamera2D::_on_destroy()
{
    // Remove from draw mode registry.
    node->engine->unregisterDrawMode(name);
}

void RayLibCamera2D::_on_update()
{
    camera.offset = offset;
    camera.target = target != nullptr ? *target : Vector2Zero();
    camera.rotation = rotation;
    camera.zoom = zoom;
}
}