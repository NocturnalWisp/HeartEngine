#pragma once

#include "heart/module.h"

#include <sol/sol.hpp>

namespace HeartRayLib { class Input; }

namespace HeartRayLib
{
//TODO: Convert include_ variables to definitions for better compilation size.
class RayLibInput : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;
    void duringUpdate(HeartEngine::Engine& engine) override;
private:
#ifdef INCLUDE_KEYBOARD
    void setupKeyboard(sol::usertype<Input>&);
#endif
#ifdef INCLUDE_MOUSE
    void setupMouse(sol::usertype<Input>&);
#endif
#ifdef INCLUDE_GAMEPAD
    void setupGamePad(sol::usertype<Input>&);
#endif
#ifdef INCLUDE_TOUCH
    void setupTouch(sol::usertype<Input>&);
#endif
};
}