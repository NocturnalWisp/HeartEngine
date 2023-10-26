#include "module/texture_rect.h"

#include "heart/component.h"

#include "module/utils.h"

namespace HeartRayLib
{
TextureRect::TextureRect(std::string name, sol::variadic_args args) : Component(name)
{
    using namespace HeartRaylib;

    // Texture Name
    CHECK_ARG(0, std::string, textureName = *result);
    // Source
    CHECK_ARG(1, std::optional<Rectangle>, source = *result);
    CHECK_ARG(1, std::vector<float>, source = tableToRectangle(*result));
    // Transform
    CHECK_ARG(2, Transform2D, transform = *result);
    CHECK_ARG(2, std::vector<float>, transform = tableToVector2(*result));
    // Origin
    CHECK_ARG(3, std::vector<float>, origin = tableToVector2(*result));

    // Color
    CHECK_ARG(4, Color, color = *result);
    // Color as int (hex)
    CHECK_ARG(4, int, color = GetColor(*result));
    // Color as vector of floats (rgba)
    CHECK_ARG(4, std::vector<float>, color = tableToColor(*result));
}

void TextureRect::populateLuaData()
{
    auto type = CREATEUSERTYPE(TextureRect);

    //TODO: Introduce texture type to lua somewhere (Probs engine.)
    type["texture"] = &TextureRect::texture;
}

void TextureRect::_on_create()
{
    setdrawCall(drawCall);

    texture = node->engine->getResource<HeartRayLib::Texture>(textureName);
}

void TextureRect::_on_destroy()
{
    texture.reset();
}

void TextureRect::_on_draw()
{
    // Origin is percentile based: 0 = start, 1 = end.
    auto actualOrigin = Vector2Multiply(origin, rect.GetSize());
    if (texture != nullptr)
    {
        auto textureSize = Vector2(texture->texture.width, texture->texture.height);

        auto actualScale = Vector2Multiply(rect.GetSize(), textureSize);

        DrawTexturePro(texture->texture,
        source.has_value() 
            ? source
            : {Vector2Zero(), textureSize},
        rect,
        origin
        rotation,
        color);
    }
    else
    {
        DrawRectanglePro(
            rect,
            origin,
            rotation,
            color
        );
    }
}

void TextureRect::set_texture(std::string p_textureName)
{
    textureName = p_textureName;
    texture = node->engine->getResource<HeartRayLib::Texture>(textureName);
}
}