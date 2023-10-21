#include "module/raylib_label.h"

#include "heart/engine.h"

namespace HeartModules
{
void Label::populateLuaData()
{
    auto type = CREATEUSERTYPE(Label);

    type["text"] = &Label::text;
}

void Label::_on_create()
{
    node->engine->events["draw"].addListener([this](){_on_draw(); });

    transform = &node->getComponentT<HeartModules::Transform3D>("Transform");
}

void Label::_on_draw()
{
    auto position = transform->getWorldPosition();
    auto scale = transform->getWorldScale();
    auto rotation = transform->getWorldRotation();

    DrawText(text.c_str(), position.x, position.y, scale.x, BLACK);
}
}