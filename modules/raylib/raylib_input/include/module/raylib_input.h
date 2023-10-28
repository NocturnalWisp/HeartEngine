#pragma once

#include "heart/module.h"

#include <sol/sol.hpp>

namespace HeartRayLib { class Input; }

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
private:
    void handleInputEvents(HeartEngine::Engine& engine);

    void setupKeyboard(sol::usertype<Input>&);
    void setupMouse(sol::usertype<Input>&);
    void setupGamePad(sol::usertype<Input>&);
    void setupTouch(sol::usertype<Input>&);

    bool includeKeyboard;
    bool includeMouse;
    bool includeGamePad;
    bool includeTouch;
};
}