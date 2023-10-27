#include "module/raylib_shapes.h"

#include "heart/engine.h"
#include "heart/utils.h"

#include "module/components/raylib_rectangle.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibShapes::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    // Rectangle.
    auto rectangleType = REGISTER_COMPONENT(Rectangle);

    ADD_LUA_FUNCTION_W_TYPE(rectangleType, Rectangle, rect);
    ADD_LUA_FUNCTION_W_TYPE(rectangleType, Rectangle, origin);
    ADD_LUA_FUNCTION_W_TYPE(rectangleType, Rectangle, rotation);
    ADD_LUA_FUNCTION_W_TYPE(rectangleType, Rectangle, color);
}
}