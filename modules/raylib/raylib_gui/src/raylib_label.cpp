#include "module/raylib_label.h"

#include "heart/engine.h"

#include "module/utils.h"

namespace HeartRayLib
{
Label::Label(std::string p_name, sol::variadic_args args)
    : Component(p_name)
{
    // Text
    CHECK_ARG(0, std::string, text = *result);
    // Position
    CHECK_ARG(1, raylib::Vector2, position = *result);
    CHECK_ARG(1, std::vector<float>, position = tableToVector2(*result));
    // Font Size
    CHECK_ARG(2, float, fontSize = *result);
    // Rotation
    CHECK_ARG(3, float, rotation = *result);

    // Color
    CHECK_ARG(4, Color, color = *result);
    // Color as int (hex)
    CHECK_ARG(4, int, color = GetColor(*result));
    // Color as vector of floats (rgba)
    CHECK_ARG(4, std::vector<float>, color = tableToColor(*result));
}

void Label::populateLuaData()
{
    auto type = CREATE_USER_TYPE(Label);

    type["text"] = &Label::text;
}

void Label::_on_create()
{
    setdrawCall(drawCall);
}

void Label::_on_draw()
{
    raylib::DrawTextPro(
        GetFontDefault(),
        text.c_str(),
        position,
        Vector2Zero(),
        rotation,
        fontSize,
        fontSize/10,
        color
    );
}
}