#pragma once

#include <raylib-cpp.hpp>

namespace HeartRayLib
{
// Following functions convert vector of floats to various types.

inline Vector2 tableToVector2(const std::vector<float>& table)
{
    if (table.size() != 2)
    {
        throw HeartEngine::HeartException({"Invalid table provided as an argument to Vector2. 2 items are required."});
    }

    Vector2 result;
    result.x = table[0];
    result.y = table[1];
    return result;
}

inline Vector3 tableToVector3(const std::vector<float>& table)
{
    if (table.size() != 2)
    {
        throw HeartEngine::HeartException({"Invalid table provided as an argument to Vector3. 3 items are required."});
    }

    Vector3 result;
    result.x = table[0];
    result.y = table[1];
    result.z = table[2];
    return result;
}

inline Rectangle tableToRectangle(const std::vector<float>& table)
{
    if (table.size() != 4)
    {
        throw HeartEngine::HeartException({"Invalid table provided as an argument to Rectangle. 4 items are required."});
    }

    Rectangle result;
    result.x = table[0];
    result.y = table[1];
    result.width = table[2];
    result.height = table[3];
    return result;
}

inline Color tableToColor(const std::vector<float>& table)
{
    if (table.size() != 4 && table.size() != 3)
    {
        throw HeartEngine::HeartException({"Invalid table provided as an argument to Color. 3 (4 with alpha) items are required."});
    }

    Color result;
    result.r = table[0];
    result.g = table[1];
    result.b = table[2];
    if (table.size() > 3)
        result.a = table[3];
    return result;
}

// Check Arg sub-macros

#define CHECK_ARG_VECTOR2(index, var) \
    CHECK_ARG_FALSE(index, Vector2, var = *result); \
    CHECK_ARG(index, std::vector<float>, var = HeartRayLib::tableToVector2(*result))

#define CHECK_ARG_COLOR(index, var) \
    CHECK_ARG_FALSE(index, Color, var = *result); \
    CHECK_ARG_FALSE(index, int, var = GetColor(*result)); \
    CHECK_ARG(index, std::vector<float>, var = HeartRayLib::tableToColor(*result))

#define CHECK_ARG_RECT(index, var) \
    CHECK_ARG_FALSE(index, Rectangle, var = *result); \
    CHECK_ARG(index, std::vector<float>, var = HeartRayLib::tableToRectangle(*result))
}