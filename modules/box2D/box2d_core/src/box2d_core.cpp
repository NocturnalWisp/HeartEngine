#include "module/box2d_core.h"

#include "heart/engine.h"

#include "box2d/box2d.h"

#include "module/box2d_global_data.h"

#include "module/components/static_body.h"

using namespace HeartEngine;

namespace HeartBox2D
{
void Box2DCore::registerTypes(Engine& engine, sol::state& lua)
{
    auto box2dType = REGISTER_GLOBAL_DATA(Box2D);

    ADD_LUA_FUNCTION_W_TYPE(box2dType, Box2D, world);
    ADD_LUA_FUNCTION_W_TYPE(box2dType, Box2D, velocityIterations);
    ADD_LUA_FUNCTION_W_TYPE(box2dType, Box2D, positionIterations);
}

void Box2DCore::initialize(Engine& engine)
{
    box2d = engine.getGlobalDataT<Box2D>("Box2D");
}

void Box2DCore::beforeFixedUpdate(Engine& engine)
{
    box2d->world.Step(engine.fixedDeltaTime, box2d->velocityIterations, box2d->positionIterations);
}
}