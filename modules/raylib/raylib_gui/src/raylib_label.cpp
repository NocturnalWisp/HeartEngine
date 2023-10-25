#include "module/raylib_label.h"

#include "heart/engine.h"

namespace HeartModules
{
Color tableToColor(const std::vector<float>& table)
{
    Color result;
    result.r = table[0];
    result.g = table[1];
    result.b = table[2];
    if (table.size() > 3)
        result.a = table[3];
    return result;
}

Label::Label(std::string p_name, sol::variadic_args args)
    : Component(p_name)
{
    // Text
    CHECK_ARG(0, std::string, text = *result);
    // Position
    CHECK_ARG(1, Vector2, position = *result);
    // Font Size
    CHECK_ARG(2, float, fontSize = *result);

    // Color
    CHECK_ARG(3, Color, color = *result);
    // Color as int (hex)
    CHECK_ARG(3, int, color = GetColor(*result));
    // Color as vector of floats (rgba)
    CHECK_ARG(3, std::vector<float>, color = tableToColor(*result));
}

void Label::populateLuaData()
{
    auto type = CREATEUSERTYPE(Label);

    type["text"] = &Label::text;
}

void Label::_on_create()
{
    setdrawCall(drawCall);
}

void Label::_on_draw()
{
    DrawText(text.c_str(), position.x, position.y, fontSize, color);
}
}