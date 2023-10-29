#include "module/raylib_shapes.h"

#include "heart/engine.h"

#include "module/components/raylib_rectangle.h"
#include "module/components/raylib_triangle.h"
#include "module/components/raylib_pixel.h"
#include "module/components/raylib_line.h"
#include "module/components/raylib_circle.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibShapes::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    // Rectangle.
    auto rectangleType = REGISTER_COMPONENT(RectangleComponent);

    ADD_LUA_FUNCTION_W_TYPE(rectangleType, RectangleComponent, rect);
    ADD_LUA_FUNCTION_W_TYPE(rectangleType, RectangleComponent, origin);
    ADD_LUA_FUNCTION_W_TYPE(rectangleType, RectangleComponent, rotation);
    ADD_LUA_FUNCTION_W_TYPE(rectangleType, RectangleComponent, color);

    // Triangle.
    auto triangleType = REGISTER_COMPONENT(Triangle);

    ADD_LUA_FUNCTION_W_TYPE(triangleType, Triangle, v1);
    ADD_LUA_FUNCTION_W_TYPE(triangleType, Triangle, v2);
    ADD_LUA_FUNCTION_W_TYPE(triangleType, Triangle, v3);
    ADD_LUA_FUNCTION_W_TYPE(triangleType, Triangle, color);

    // Pixel.
    auto pixelType = REGISTER_COMPONENT(Pixel);

    ADD_LUA_FUNCTION_W_TYPE(pixelType, Pixel, position);
    ADD_LUA_FUNCTION_W_TYPE(pixelType, Pixel, color);

    // Line.
    auto lineType = REGISTER_COMPONENT(Line);

    ADD_LUA_FUNCTION_W_TYPE(lineType, Line, start);
    ADD_LUA_FUNCTION_W_TYPE(lineType, Line, end);
    ADD_LUA_FUNCTION_W_TYPE(lineType, Line, thickness);
    ADD_LUA_FUNCTION_W_TYPE(lineType, Line, color);

    // Circle.
    auto circleType = REGISTER_COMPONENT(Circle);

    ADD_LUA_FUNCTION_W_TYPE(circleType, Circle, center);
    ADD_LUA_FUNCTION_W_TYPE(circleType, Circle, radius);
    ADD_LUA_FUNCTION_W_TYPE(circleType, Circle, color);
}
}