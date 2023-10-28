#include "module/raylib_gui.h"

#include <raylib-cpp.hpp>
#include <sol/sol.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "heart/engine.h"

#include "module/components/raylib_label.h"
#include "module/components/raylib_button.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibGUI::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    auto labelType = REGISTER_COMPONENT(Label);

    ADD_LUA_FUNCTION_W_TYPE(labelType, Label, text);

    auto buttonType = REGISTER_COMPONENT(Button);

    ADD_LUA_FUNCTION_W_TYPE(buttonType, Button, rect);
    ADD_LUA_FUNCTION_W_TYPE(buttonType, Button, origin);
    ADD_LUA_FUNCTION_W_TYPE(buttonType, Button, rotation);
    ADD_LUA_FUNCTION_W_TYPE(buttonType, Button, color);
}
}