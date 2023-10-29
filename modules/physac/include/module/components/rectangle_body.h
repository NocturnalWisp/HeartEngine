#pragma once

#include <raylib-cpp.hpp>

#include "heart/engine.h"

#include "module/utils.h"

#include "module/physac_core.h"

namespace HeartPhysac { class PhysacCore; }

using namespace HeartEngine;

namespace HeartPhysac
{
class RectanglePhysicsBody : public HeartEngine::Component
{
    SETUP_COMPONENT()

    friend class PhysacCore;
public:
    RectanglePhysicsBody(std::string name,
        Rectangle rect, float density = 10)
        : Component(name)
    {
        body = PhysacCore::CreatePhysicsBodyRectangleWrapper({rect.x, rect.y}, rect.width, rect.height, density);
    }
    RectanglePhysicsBody(std::string name, sol::variadic_args args)
        : Component(name)
    {
        Rectangle rect;
        float density;

        CHECK_ARG_RECT(0, rect);
        CHECK_ARG_FLOAT(1, density);

        body = PhysacCore::CreatePhysicsBodyRectangleWrapper({rect.x, rect.y}, rect.width, rect.height, density);
    }

    void addForce(Vector2 force) { PhysacCore::PhysicsAddForceWrapper(body, force); }
    void addTorque(float amount) { PhysacCore::PhysicsAddTorqueWrapper(body, amount); }
    void setRotation(float amount) { PhysacCore::SetPhysicsBodyRotationWrapper(body, DEG2RAD * amount); }

    PhysicsBody body;

    void _on_destroy() override
    {
        PhysacCore::DestroyPhysicsBodyWrapper(body);
    }
};
}