#include "module/raylib_input.h"

#include <sol/sol.hpp>
#include <raylib-cpp.hpp>

#include "heart/utils.h"
#include "heart/engine.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibInput::registerTypes(HeartEngine::Engine &engine, sol::state &lua)
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
void RayLibInput::duringUpdate(HeartEngine::Engine& engine)
{
    PollInputEvents();

    handleInputEvents(engine);
}

void RayLibInput::handleInputEvents(HeartEngine::Engine& engine)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        engine.events["input"]["mouse"]["left"]["pressed"].run();
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        engine.events["input"]["mouse"]["left"]["released"].run();

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        engine.events["input"]["mouse"]["right"]["pressed"].run();
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        engine.events["input"]["mouse"]["right"]["released"].run();
    
    auto key = GetKeyPressed();
    while (key != 0)
    {
        engine.events["input"]["keyboard"][std::to_string(key)].run();
    }
}

void RayLibInput::SetupKeyboard(sol::state& input)
{
    ADD_LUA_COPY(input, KEY_ESCAPE);
    ADD_LUA_COPY(input, KEY_F1);
    ADD_LUA_COPY(input, KEY_F2);
    ADD_LUA_COPY(input, KEY_F3);
    ADD_LUA_COPY(input, KEY_F4);
    ADD_LUA_COPY(input, KEY_F5);
    ADD_LUA_COPY(input, KEY_F6);
    ADD_LUA_COPY(input, KEY_F7);
    ADD_LUA_COPY(input, KEY_F8);
    ADD_LUA_COPY(input, KEY_F9);
    ADD_LUA_COPY(input, KEY_F10);
    ADD_LUA_COPY(input, KEY_F11);
    ADD_LUA_COPY(input, KEY_F12);
    ADD_LUA_COPY(input, KEY_PRINT_SCREEN);
    ADD_LUA_COPY(input, KEY_SCROLL_LOCK);
    ADD_LUA_COPY(input, KEY_PAUSE);
    ADD_LUA_COPY(input, KEY_GRAVE);
    ADD_LUA_COPY(input, KEY_MINUS);
    ADD_LUA_COPY(input, KEY_EQUAL);
    ADD_LUA_COPY(input, KEY_BACKSPACE);
    ADD_LUA_COPY(input, KEY_INSERT);
    ADD_LUA_COPY(input, KEY_HOME);
    ADD_LUA_COPY(input, KEY_PAGE_UP);
    ADD_LUA_COPY(input, KEY_NUM_LOCK);

    ADD_LUA_COPY(input, KEY_ONE);
    ADD_LUA_COPY(input, KEY_TWO);
    ADD_LUA_COPY(input, KEY_THREE);
    ADD_LUA_COPY(input, KEY_FOUR);
    ADD_LUA_COPY(input, KEY_FIVE);
    ADD_LUA_COPY(input, KEY_SIX);
    ADD_LUA_COPY(input, KEY_SEVEN);
    ADD_LUA_COPY(input, KEY_EIGHT);
    ADD_LUA_COPY(input, KEY_NINE);
    ADD_LUA_COPY(input, KEY_ZERO);

    ADD_LUA_COPY(input, KEY_KP_1);
    ADD_LUA_COPY(input, KEY_KP_2);
    ADD_LUA_COPY(input, KEY_KP_3);
    ADD_LUA_COPY(input, KEY_KP_4);
    ADD_LUA_COPY(input, KEY_KP_5);
    ADD_LUA_COPY(input, KEY_KP_6);
    ADD_LUA_COPY(input, KEY_KP_7);
    ADD_LUA_COPY(input, KEY_KP_8);
    ADD_LUA_COPY(input, KEY_KP_9);
    ADD_LUA_COPY(input, KEY_KP_ADD);
    ADD_LUA_COPY(input, KEY_KP_DIVIDE);
    ADD_LUA_COPY(input, KEY_KP_MULTIPLY);
    ADD_LUA_COPY(input, KEY_KP_SUBTRACT);
    ADD_LUA_COPY(input, KEY_KP_DECIMAL);
    ADD_LUA_COPY(input, KEY_KP_ENTER);
    ADD_LUA_COPY(input, KEY_KP_EQUAL);
    ADD_LUA_COPY(input, KEY_KB_MENU);

    ADD_LUA_COPY(input, KEY_TAB);
    ADD_LUA_COPY(input, KEY_BACKSLASH);
    ADD_LUA_COPY(input, KEY_DELETE);
    ADD_LUA_COPY(input, KEY_END);
    ADD_LUA_COPY(input, KEY_PAGE_DOWN);

    ADD_LUA_COPY(input, KEY_A);
    ADD_LUA_COPY(input, KEY_B);
    ADD_LUA_COPY(input, KEY_C);
    ADD_LUA_COPY(input, KEY_D);
    ADD_LUA_COPY(input, KEY_E);
    ADD_LUA_COPY(input, KEY_F);
    ADD_LUA_COPY(input, KEY_G);
    ADD_LUA_COPY(input, KEY_H);
    ADD_LUA_COPY(input, KEY_I);
    ADD_LUA_COPY(input, KEY_J);
    ADD_LUA_COPY(input, KEY_K);
    ADD_LUA_COPY(input, KEY_L);
    ADD_LUA_COPY(input, KEY_M);
    ADD_LUA_COPY(input, KEY_N);
    ADD_LUA_COPY(input, KEY_O);
    ADD_LUA_COPY(input, KEY_P);
    ADD_LUA_COPY(input, KEY_Q);
    ADD_LUA_COPY(input, KEY_R);
    ADD_LUA_COPY(input, KEY_S);
    ADD_LUA_COPY(input, KEY_T);
    ADD_LUA_COPY(input, KEY_U);
    ADD_LUA_COPY(input, KEY_V);
    ADD_LUA_COPY(input, KEY_W);
    ADD_LUA_COPY(input, KEY_X);
    ADD_LUA_COPY(input, KEY_Y);
    ADD_LUA_COPY(input, KEY_Z);
    ADD_LUA_COPY(input, KEY_PERIOD);
    ADD_LUA_COPY(input, KEY_COMMA);
    ADD_LUA_COPY(input, KEY_SLASH);
    ADD_LUA_COPY(input, KEY_SEMICOLON);
    ADD_LUA_COPY(input, KEY_APOSTROPHE);

    ADD_LUA_COPY(input, KEY_SPACE);
    ADD_LUA_COPY(input, KEY_CAPS_LOCK);
    ADD_LUA_COPY(input, KEY_LEFT_SHIFT);
    ADD_LUA_COPY(input, KEY_RIGHT_SHIFT);
    ADD_LUA_COPY(input, KEY_LEFT_CONTROL);
    ADD_LUA_COPY(input, KEY_RIGHT_CONTROL);
    ADD_LUA_COPY(input, KEY_LEFT_ALT);
    ADD_LUA_COPY(input, KEY_RIGHT_ALT);
    ADD_LUA_COPY(input, KEY_LEFT_SUPER);
    ADD_LUA_COPY(input, KEY_RIGHT_SUPER);
    ADD_LUA_COPY(input, KEY_MENU);

    ADD_LUA_COPY(input, KEY_LEFT_BRACKET);
    ADD_LUA_COPY(input, KEY_RIGHT_BRACKET);

    ADD_LUA_COPY(input, KEY_UP);
    ADD_LUA_COPY(input, KEY_DOWN);
    ADD_LUA_COPY(input, KEY_LEFT);
    ADD_LUA_COPY(input, KEY_RIGHT);
}
void RayLibInput::SetupMouse(sol::state& input)
{
    ADD_LUA_COPY(input, MOUSE_BUTTON_BACK);
    ADD_LUA_COPY(input, MOUSE_BUTTON_EXTRA);
    ADD_LUA_COPY(input, MOUSE_BUTTON_FORWARD);
    ADD_LUA_COPY(input, MOUSE_BUTTON_LEFT);
    ADD_LUA_COPY(input, MOUSE_BUTTON_MIDDLE);
    ADD_LUA_COPY(input, MOUSE_BUTTON_RIGHT);
    ADD_LUA_COPY(input, MOUSE_BUTTON_SIDE);

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
void RayLibInput::SetupGamePad(sol::state& input)
{
    //TODO:
}
void RayLibInput::SetupTouch(sol::state& input)
{
    //TODO:
}
}