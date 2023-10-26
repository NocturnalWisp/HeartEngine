#pragma once

#include <sol/sol.hpp>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartRayLib
{
class RayMath : public HeartEngine::Module
{
public:
    RayMath(bool includeVector2 = true,
            bool includeVector3 = true,
            bool includeMatrix = true,
            bool includeQuaternion = true)
        : includeVector2(includeVector2),
        includeVector3(includeVector3),
        includeMatrix(includeMatrix),
        includeQuaternion(includeQuaternion) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        if (includeVector2)
            SetupVector2(lua);
        if (includeVector3)
            SetupVector3(lua);
        if (includeMatrix)
            SetupMatrix(lua);
        if (includeQuaternion)
            SetupQuaternion(lua);
        SetupOther(lua);
    }

    void SetupVector2(sol::state& lua);
    void SetupVector3(sol::state& lua);
    void SetupMatrix(sol::state& lua);
    void SetupQuaternion(sol::state& lua);
    void SetupOther(sol::state& lua);
private:
    bool includeVector2;
    bool includeVector3;
    bool includeMatrix;
    bool includeQuaternion;
};
}