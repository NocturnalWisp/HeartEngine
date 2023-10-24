#include "module/raylib_label.h"

#include "heart/engine.h"

namespace HeartModules
{
Label::Label(std::string p_name, sol::variadic_args args)
    : Component(p_name)
{
    const short textIndex = 0;

    if (auto p_text = checkArg<std::string>(args[textIndex]))
        text = *p_text;
}

void Label::populateLuaData()
{
    auto type = CREATEUSERTYPE(Label);

    type["text"] = &Label::text;
}

void Label::_on_create()
{
    SetDrawCall(drawCall);
}

void Label::_on_draw()
{
    auto position = transform->getWorldPosition();
    auto scale = transform->getWorldScale();
    auto rotation = transform->getWorldRotation();

    DrawText(text.c_str(), position.x, position.y, scale.x, BLACK);
}
}