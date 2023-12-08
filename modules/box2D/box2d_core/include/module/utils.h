#pragma once

#include <box2d/b2_math.h>

namespace HeartBox2D
{
// Following functions convert vector of floats to various types.

inline b2Vec2 tableToVector2(const std::vector<float>& table)
{
    if (table.size() != 2)
    {
        throw HeartEngine::HeartException({"Invalid table provided as an argument to Vector2. 2 items are required."});
    }

    b2Vec2 result;
    result.x = table[0];
    result.y = table[1];
    return result;
}

// Check Arg sub-macros

#define CHECK_ARG_VECTOR2(index, var) \
    CHECK_ARG_FALSE(index, b2Vec2, var = *result); \
    CHECK_ARG(index, std::vector<float>, var = HeartBox2D::tableToVector2(*result))
}