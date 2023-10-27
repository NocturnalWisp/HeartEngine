#pragma once

#include "heart/module.h"

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

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;
    void duringUpdate(HeartEngine::Engine& engine) override;

    void SetupKeyboard(sol::state&);
    void SetupMouse(sol::state&);
    void SetupGamePad(sol::state&);
    void SetupTouch(sol::state&);
private:
    void handleInputEvents(HeartEngine::Engine& engine);

    bool includeKeyboard;
    bool includeMouse;
    bool includeGamePad;
    bool includeTouch;
};
}