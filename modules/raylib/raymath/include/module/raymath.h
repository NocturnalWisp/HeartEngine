#pragma once

#include "heart/module.h"

namespace HeartRayLib
{
class RayMath : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;

#ifdef INCLUDE_VECTOR2
    void SetupVector2(sol::state& lua);
#endif
#ifdef INCLUDE_VECTOR3
    void SetupVector3(sol::state& lua);
#endif
#ifdef INCLUDE_MATRIX
    void SetupMatrix(sol::state& lua);
#endif
#ifdef INCLUDE_QUATERNION
    void SetupQuaternion(sol::state& lua);
#endif
};
}