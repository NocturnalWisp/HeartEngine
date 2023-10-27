#pragma once

#include <raylib-cpp.hpp>
#include <sol/sol.hpp>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartRayLib
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

    static bool CheckCollisionPointRec(raylib::Vector2 point, raylib::Rectangle rec)
    {
        bool collision = false;

        if ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) &&
            (point.y >= rec.y) && (point.y <= (rec.y + rec.height))) collision = true;

        return collision;
    }
private:
    bool includeSetting;
};
}