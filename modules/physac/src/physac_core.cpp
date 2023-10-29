#include "module/physac_core.h"

#include <sol/sol.hpp>

#include "heart/engine.h"

#include "module/components/rectangle_body.h"

#include "raylib.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

#undef min
#undef max

using namespace HeartEngine;

namespace HeartPhysac
{
void PhysacCore::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    auto rectangleBodyType = REGISTER_COMPONENT(RectanglePhysicsBody);

    ADD_LUA_FUNCTION_W_TYPE(rectangleBodyType, RectanglePhysicsBody, body);

    ADD_LUA_FUNCTION_W_TYPE(rectangleBodyType, RectanglePhysicsBody, addForce);
    ADD_LUA_FUNCTION_W_TYPE(rectangleBodyType, RectanglePhysicsBody, addTorque);
    ADD_LUA_FUNCTION_W_TYPE(rectangleBodyType, RectanglePhysicsBody, setRotation);

    auto physicsBodyType = lua.new_usertype<PhysicsBodyData>("PhysicsBody");

    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, id);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, enabled);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, position);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, velocity);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, force);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, angularVelocity);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, torque);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, orient);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, inertia);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, mass);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, staticFriction);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, dynamicFriction);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, restitution);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, useGravity);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, isGrounded);
    ADD_LUA_FUNCTION_W_TYPE(physicsBodyType, PhysicsBodyData, freezeOrient);
}

void PhysacCore::initialize(HeartEngine::Engine& engine)
{
    InitPhysics();

    SetPhysicsGravity(0, 0.3);
}

void PhysacCore::close(HeartEngine::Engine& engine)
{
    ClosePhysics();
}

PhysicsBody PhysacCore::CreatePhysicsBodyRectangleWrapper(Vector2 pos, float width, float height, float density)
{
    return CreatePhysicsBodyRectangle(pos, width, height, density);
}

void PhysacCore::PhysicsAddForceWrapper(PhysicsBody body, Vector2 force)
{
    PhysicsAddForce(body, force);
}
void PhysacCore::PhysicsAddTorqueWrapper(PhysicsBody body, float amount)
{
    PhysicsAddTorque(body, amount);
}
void PhysacCore::SetPhysicsBodyRotationWrapper(PhysicsBody body, float radians)
{
    SetPhysicsBodyRotation(body, radians);
}
void PhysacCore::DestroyPhysicsBodyWrapper(PhysicsBody body)
{
    DestroyPhysicsBody(body);
}
}