#pragma once

#include <sol/sol.hpp>
#include <raylib-cpp.hpp>

#include "heart/module.h"

#include "heart/debug.h"

namespace HeartModules
{
class RayMath : public HeartEngine::Module
{
public:
    void registerTypes(sol::state& lua) override
    {
        sol::table table = lua.create_named_table("RayMath");

        SetupVector2(lua);
        SetupVector3(lua);
        SetupMatrix(lua);
        SetupQuaternion(lua);
        SetupOther(lua);
    }

    void SetupVector2(sol::state& lua);
    void SetupVector3(sol::state& lua);
    void SetupMatrix(sol::state& lua);
    void SetupQuaternion(sol::state& lua);
    void SetupOther(sol::state& lua);
};
}