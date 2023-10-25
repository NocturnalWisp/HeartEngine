#pragma once

#include <sol/sol.hpp>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartModules
{
class RayLibGUI : public HeartEngine::Module
{
public:
    RayLibGUI(bool includeSetting = true)
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