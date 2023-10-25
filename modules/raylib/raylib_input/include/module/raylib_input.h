#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include "heart/module.h"

namespace HeartEngine { class Engine; }

namespace HeartRayLib
{
class RayLibInput : public HeartEngine::Module
{
public:
    RayLibInput(bool includeKeyboard = true,
                bool includeMouse = true,
                bool includeGamePad = false,
                bool includeTouch = false)
        : includeKeyboard(includeKeyboard),
          includeMouse(includeMouse),
          includeGamePad(includeGamePad),
          includeTouch(includeTouch) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        if (includeKeyboard)
            SetupKeyboard(lua);
        if (includeMouse)
            SetupMouse(lua);
        if (includeGamePad)
            SetupGamePad(lua);
        if (includeTouch)
            SetupTouch(lua);
    }

    void SetupKeyboard(sol::state&);
    void SetupMouse(sol::state&);
    void SetupGamePad(sol::state&);
    void SetupTouch(sol::state&);
private:
    bool includeKeyboard;
    bool includeMouse;
    bool includeGamePad;
    bool includeTouch;
};
}