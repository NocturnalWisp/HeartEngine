#pragma once

#include "heart/module.h"

namespace HeartRayLib
{
class RayMath : public HeartEngine::Module
{
public:
    RayMath(bool includeVector2 = true,
            bool includeVector3 = true,
            bool includeMatrix = false,
            bool includeQuaternion = false)
        : includeVector2(includeVector2),
        includeVector3(includeVector3),
        includeMatrix(includeMatrix),
        includeQuaternion(includeQuaternion) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;

    void SetupVector2(sol::state& lua);
    void SetupVector3(sol::state& lua);
    void SetupMatrix(sol::state& lua);
    void SetupQuaternion(sol::state& lua);
private:
    bool includeVector2;
    bool includeVector3;
    bool includeMatrix;
    bool includeQuaternion;
};
}