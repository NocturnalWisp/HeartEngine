#include "module/raylib_gui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "heart/utils.h"
#include "heart/engine.h"

#include "module/raylib_label.h"
#include "module/raylib_button.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibGUI::Setup(HeartEngine::Engine& engine, sol::state& lua)
{
    REGISTER_COMPONENT(Label);
    REGISTER_COMPONENT(Button);
}
}