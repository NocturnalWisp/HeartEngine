#pragma once

#include <raylib-cpp.hpp>

using namespace HeartEngine;

namespace HeartRayLib
{
struct Transform2D
{
public:
    Transform2D(
        Vector2 position = Vector2Zero(),
        Vector2 scale = Vector2Zero(),
        float rotation = 0
    ) : position(position), scale(scale), rotation(rotation) {}

    Vector2 position;
    Vector2 scale;
    float rotation;
};

Transform2D tableToTransform2D(const std::vector<float>& table)
{
    if (table.size() != 5)
    {
        throw HeartException({"Invalid table provided as an argument to Transform2D. 5 items are required. (2 position, 2 scale, 1 rotation)"});
    }

    Transform2D result;
    result.position.x = table[0];
    result.position.y = table[1];
    result.scale.x = table[2];
    result.scale.y = table[3];
    result.rotation = table[4];
    return result;
}
}