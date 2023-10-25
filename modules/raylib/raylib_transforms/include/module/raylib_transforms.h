#pragma once

#include <sol/sol.hpp>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartRayLib
{
class RayLibTransforms : public HeartEngine::Module
{
public:
    RayLibTransforms(bool includeSetting = true)
        : includeSetting(includeSetting) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        if (includeSetting)
            Setup(engine, lua);
    }

    void Setup(HeartEngine::Engine& engine, sol::state& lua);
private:
    bool includeSetting;
};
}