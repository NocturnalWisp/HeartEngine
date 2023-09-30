#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

using namespace HeartEngine;

namespace HeartModules
{
class Transforms : public HeartEngine::Module
{
public:
    Transforms(bool includeTransform2D = true,
            bool includeTransform3D = true)
        : includeTransform2D(includeTransform2D),
        includeTransform3D(includeTransform3D) {}

    void registerTypes(Engine& engine, sol::state& lua) override
    {
        if (includeTransform2D)
            SetupTransform2D(engine, lua);
        if (includeTransform3D)
            SetupTransform3D(engine, lua);
    }

    void SetupTransform2D(Engine& engine, sol::state& lua);
    void SetupTransform3D(Engine& engine, sol::state& lua);
private:
    bool includeTransform2D;
    bool includeTransform3D;
};
}