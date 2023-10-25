#include "module/raylib_transforms.h"

#include "heart/engine.h"

#include "heart/utils.h"

#include "module/transform2d.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibTransforms::Setup(HeartEngine::Engine& engine, sol::state& lua)
{
    auto type = lua.new_usertype<Transform2D>("Transform2D");

    ADD_LUA_FUNCTION_W_TYPE(type, Transform2D, position);
    ADD_LUA_FUNCTION_W_TYPE(type, Transform2D, scale);
    ADD_LUA_FUNCTION_W_TYPE(type, Transform2D, rotation);
}
}