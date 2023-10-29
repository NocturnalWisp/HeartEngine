#pragma once

// Yuck two libs sharing these macros (Physac, Chrono)
#undef min
#undef max

#include "heart/module.h"

namespace HeartPhysac { class RectanglePhysicsBody; }

class PhysicsBodyData;
typedef PhysicsBodyData *PhysicsBody;

class Vector2;

namespace HeartPhysac
{
//TODO:? Possibly make it independant from raylib depending on compile definitions?
//TODO: Add physics global data object for setting gravity, resetting physics world. etc...
class PhysacCore : public HeartEngine::Module
{
    // This library is nasty and can only be defined once (in the cpp file)
    // so we need to friend the classes so they can call the functions as a sort of wrapper.
    friend class RectanglePhysicsBody;
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;

    void initialize(HeartEngine::Engine& engine) override;
    void close(HeartEngine::Engine& engine) override;


    static PhysicsBody CreatePhysicsBodyRectangleWrapper(Vector2 pos, float width, float height, float density);
    static void PhysicsAddForceWrapper(PhysicsBody body, Vector2 force);                                            // Adds a force to a physics body
    static void PhysicsAddTorqueWrapper(PhysicsBody body, float amount);                                            // Adds an angular force to a physics body
    static void SetPhysicsBodyRotationWrapper(PhysicsBody body, float radians);                                     // Sets physics body shape transform based on radians parameter
    static void DestroyPhysicsBodyWrapper(PhysicsBody body);
};
}