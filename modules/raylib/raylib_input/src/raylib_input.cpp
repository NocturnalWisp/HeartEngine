#include "module/raylib_input.h"

#include <sol/sol.hpp>
#include <raylib-cpp.hpp>

#include "heart/engine.h"

#include "module/input_global_data.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibInput::registerTypes(HeartEngine::Engine &engine, sol::state &lua)
{
    auto inputType = lua.new_usertype<Input>("Input");

    if (includeKeyboard)
        setupKeyboard(inputType);
    if (includeMouse)
        setupMouse(inputType);
    if (includeGamePad)
        setupGamePad(inputType);
    if (includeTouch)
        setupTouch(inputType);

    engine.registerGlobalData(Input());
}
void RayLibInput::duringUpdate(HeartEngine::Engine& engine)
{
    PollInputEvents();
}

void RayLibInput::setupKeyboard(sol::usertype<Input>& input)
{
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_ESCAPE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F1);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F2);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F3);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F4);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F5);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F6);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F7);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F8);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F9);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F10);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F11);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F12);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_PRINT_SCREEN);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_SCROLL_LOCK);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_PAUSE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_GRAVE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_MINUS);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_EQUAL);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_BACKSPACE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_INSERT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_HOME);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_PAGE_UP);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_NUM_LOCK);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_ONE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_TWO);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_THREE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_FOUR);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_FIVE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_SIX);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_SEVEN);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_EIGHT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_NINE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_ZERO);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_1);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_2);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_3);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_4);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_5);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_6);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_7);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_8);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_9);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_ADD);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_DIVIDE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_MULTIPLY);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_SUBTRACT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_DECIMAL);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_ENTER);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KP_EQUAL);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_KB_MENU);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_TAB);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_BACKSLASH);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_DELETE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_END);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_PAGE_DOWN);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_A);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_B);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_C);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_D);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_E);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_F);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_G);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_H);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_I);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_J);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_K);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_L);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_M);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_N);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_O);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_P);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_Q);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_R);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_S);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_T);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_U);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_V);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_W);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_X);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_Y);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_Z);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_PERIOD);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_COMMA);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_SLASH);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_SEMICOLON);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_APOSTROPHE);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_SPACE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_CAPS_LOCK);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_LEFT_SHIFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_RIGHT_SHIFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_LEFT_CONTROL);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_RIGHT_CONTROL);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_LEFT_ALT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_RIGHT_ALT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_LEFT_SUPER);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_RIGHT_SUPER);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_MENU);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_LEFT_BRACKET);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_RIGHT_BRACKET);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_UP);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_DOWN);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_LEFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, KEY_RIGHT);

    ADD_LUA_FUNCTION(input, IsKeyPressed);
    ADD_LUA_FUNCTION(input, IsKeyDown);
    ADD_LUA_FUNCTION(input, IsKeyReleased);
    ADD_LUA_FUNCTION(input, IsKeyUp);
    ADD_LUA_FUNCTION(input, SetExitKey);
    ADD_LUA_FUNCTION(input, GetKeyPressed);
    ADD_LUA_FUNCTION(input, GetCharPressed);
}
void RayLibInput::setupMouse(sol::usertype<Input>& input)
{
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_BACK);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_EXTRA);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_FORWARD);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_LEFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_MIDDLE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_RIGHT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, MOUSE_BUTTON_SIDE);

    ADD_LUA_FUNCTION(input, IsMouseButtonDown);
    ADD_LUA_FUNCTION(input, IsMouseButtonPressed);
    ADD_LUA_FUNCTION(input, IsMouseButtonReleased);
    ADD_LUA_FUNCTION(input, IsMouseButtonUp);
    ADD_LUA_FUNCTION(input, GetMouseX);
    ADD_LUA_FUNCTION(input, GetMouseY);
    ADD_LUA_FUNCTION(input, GetMousePosition);
    ADD_LUA_FUNCTION(input, GetMouseDelta);
    ADD_LUA_FUNCTION(input, SetMousePosition);
    ADD_LUA_FUNCTION(input, SetMouseOffset);
    ADD_LUA_FUNCTION(input, SetMouseScale);
    ADD_LUA_FUNCTION(input, GetMouseWheelMove);
    ADD_LUA_FUNCTION(input, GetMouseWheelMoveV);
    ADD_LUA_FUNCTION(input, SetMouseCursor);
}
void RayLibInput::setupGamePad(sol::usertype<Input>& input)
{
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_UNKNOWN);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_FACE_UP);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_FACE_UP);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_MIDDLE_LEFT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_MIDDLE);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_LEFT_THUMB);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_BUTTON_RIGHT_THUMB);

    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_AXIS_LEFT_X);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_AXIS_LEFT_Y);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_AXIS_RIGHT_X);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_AXIS_RIGHT_Y);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_AXIS_LEFT_TRIGGER);
    ADD_LUA_FUNCTION_W_TYPE(input, Input, GAMEPAD_AXIS_RIGHT_TRIGGER);

    ADD_LUA_FUNCTION(input, IsGamepadAvailable);
    ADD_LUA_FUNCTION(input, GetGamepadName);
    ADD_LUA_FUNCTION(input, IsGamepadButtonDown);
    ADD_LUA_FUNCTION(input, IsGamepadButtonPressed);
    ADD_LUA_FUNCTION(input, IsGamepadButtonReleased);
    ADD_LUA_FUNCTION(input, IsGamepadButtonUp);
    ADD_LUA_FUNCTION(input, GetGamepadButtonPressed);
    ADD_LUA_FUNCTION(input, GetGamepadAxisCount);
    ADD_LUA_FUNCTION(input, GetGamepadAxisMovement);
    ADD_LUA_FUNCTION(input, SetGamepadMappings);
}
void RayLibInput::setupTouch(sol::usertype<Input>& input)
{
    //TODO:
}
}