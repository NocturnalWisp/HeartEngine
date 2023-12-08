#pragma once

#include "box2d/box2d.h"

#include "heart/global_data.h"

namespace HeartBox2D
{
class Box2D : public HeartEngine::GlobalData
{
    SETUP_GLOBAL_DATA(Box2D)
public:
    int velocityIterations = 6;
    int positionIterations = 2;

    b2World world = b2World(b2Vec2(0, -10.0f));
};
}