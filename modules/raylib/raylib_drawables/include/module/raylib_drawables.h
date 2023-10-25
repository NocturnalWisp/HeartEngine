#pragma once

#include <sol/sol.hpp>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartModules
{
class Drawables : public HeartEngine::Module
{
public:
    Drawables(bool includeTextures = true,
            bool includeShapes = true,
            bool includeLines = false,
            bool includeCollisionChecking = false)
        : includeTextures(includeTextures),
        includeShapes(includeShapes),
        includeLines(includeLines),
        includeCollisionChecking(includeCollisionChecking) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        if (includeTextures)
            SetupTextures(engine, lua);
        if (includeShapes)
            SetupShapes(engine, lua);
        if (includeLines)
            SetupLines(engine, lua);
        if (includeCollisionChecking)
            SetupCollisionChecking(engine, lua);
    }

    void SetupTextures(HeartEngine::Engine& engine, sol::state& lua);
    void SetupShapes(HeartEngine::Engine& engine, sol::state& lua);
    void SetupLines(HeartEngine::Engine& engine, sol::state& lua);
    void SetupCollisionChecking(HeartEngine::Engine& engine, sol::state& lua);
private:
    bool includeTextures;
    bool includeShapes;
    bool includeLines;
    bool includeCollisionChecking;
};
}