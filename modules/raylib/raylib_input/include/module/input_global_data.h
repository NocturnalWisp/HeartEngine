#pragma once

#include "heart/global_data.h"

namespace HeartRayLib
{
class Input : public HeartEngine::GlobalData
{
    SETUP_GLOBAL_DATA(Input)

public:
#define KEY(name) \
    const KeyboardKey name = KeyboardKey::name 

    KEY(KEY_ESCAPE);
    KEY(KEY_F1);
    KEY(KEY_F2);
    KEY(KEY_F3);
    KEY(KEY_F4);
    KEY(KEY_F5);
    KEY(KEY_F6);
    KEY(KEY_F7);
    KEY(KEY_F8);
    KEY(KEY_F9);
    KEY(KEY_F10);
    KEY(KEY_F11);
    KEY(KEY_F12);
    KEY(KEY_PRINT_SCREEN);
    KEY(KEY_SCROLL_LOCK);
    KEY(KEY_PAUSE);
    KEY(KEY_GRAVE);
    KEY(KEY_MINUS);
    KEY(KEY_EQUAL);
    KEY(KEY_BACKSPACE);
    KEY(KEY_INSERT);
    KEY(KEY_HOME);
    KEY(KEY_PAGE_UP);
    KEY(KEY_NUM_LOCK);

    KEY(KEY_ONE);
    KEY(KEY_TWO);
    KEY(KEY_THREE);
    KEY(KEY_FOUR);
    KEY(KEY_FIVE);
    KEY(KEY_SIX);
    KEY(KEY_SEVEN);
    KEY(KEY_EIGHT);
    KEY(KEY_NINE);
    KEY(KEY_ZERO);

    KEY(KEY_KP_1);
    KEY(KEY_KP_2);
    KEY(KEY_KP_3);
    KEY(KEY_KP_4);
    KEY(KEY_KP_5);
    KEY(KEY_KP_6);
    KEY(KEY_KP_7);
    KEY(KEY_KP_8);
    KEY(KEY_KP_9);
    KEY(KEY_KP_ADD);
    KEY(KEY_KP_DIVIDE);
    KEY(KEY_KP_MULTIPLY);
    KEY(KEY_KP_SUBTRACT);
    KEY(KEY_KP_DECIMAL);
    KEY(KEY_KP_ENTER);
    KEY(KEY_KP_EQUAL);
    KEY(KEY_KB_MENU);

    KEY(KEY_TAB);
    KEY(KEY_BACKSLASH);
    KEY(KEY_DELETE);
    KEY(KEY_END);
    KEY(KEY_PAGE_DOWN);

    KEY(KEY_A);
    KEY(KEY_B);
    KEY(KEY_C);
    KEY(KEY_D);
    KEY(KEY_E);
    KEY(KEY_F);
    KEY(KEY_G);
    KEY(KEY_H);
    KEY(KEY_I);
    KEY(KEY_J);
    KEY(KEY_K);
    KEY(KEY_L);
    KEY(KEY_M);
    KEY(KEY_N);
    KEY(KEY_O);
    KEY(KEY_P);
    KEY(KEY_Q);
    KEY(KEY_R);
    KEY(KEY_S);
    KEY(KEY_T);
    KEY(KEY_U);
    KEY(KEY_V);
    KEY(KEY_W);
    KEY(KEY_X);
    KEY(KEY_Y);
    KEY(KEY_Z);
    KEY(KEY_PERIOD);
    KEY(KEY_COMMA);
    KEY(KEY_SLASH);
    KEY(KEY_SEMICOLON);
    KEY(KEY_APOSTROPHE);

    KEY(KEY_SPACE);
    KEY(KEY_CAPS_LOCK);
    KEY(KEY_LEFT_SHIFT);
    KEY(KEY_RIGHT_SHIFT);
    KEY(KEY_LEFT_CONTROL);
    KEY(KEY_RIGHT_CONTROL);
    KEY(KEY_LEFT_ALT);
    KEY(KEY_RIGHT_ALT);
    KEY(KEY_LEFT_SUPER);
    KEY(KEY_RIGHT_SUPER);
    KEY(KEY_MENU);

    KEY(KEY_LEFT_BRACKET);
    KEY(KEY_RIGHT_BRACKET);

    KEY(KEY_UP);
    KEY(KEY_DOWN);
    KEY(KEY_LEFT);
    KEY(KEY_RIGHT);

#define MOUSE(name) \
    const MouseButton name = MouseButton::name

    MOUSE(MOUSE_BUTTON_BACK);
    MOUSE(MOUSE_BUTTON_EXTRA);
    MOUSE(MOUSE_BUTTON_FORWARD);
    MOUSE(MOUSE_BUTTON_LEFT);
    MOUSE(MOUSE_BUTTON_MIDDLE);
    MOUSE(MOUSE_BUTTON_RIGHT);
    MOUSE(MOUSE_BUTTON_SIDE);
};
}