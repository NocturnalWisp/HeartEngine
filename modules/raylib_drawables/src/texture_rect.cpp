#include "module/texture_rect.h"

#include "heart/component.h"

namespace HeartModules
{
TextureRect::TextureRect(std::string name, sol::variadic_args va) : Component(name)
{
    const short textureIndex = 0;

    if (auto p_textureName = checkArg<std::string>(args[textureIndex]))
        textureName = p_textureName;
}

void TextureRect::populateLuaData()
{
    auto type = CREATEUSERTYPE(TextureRect);

    //TODO: Introduce texture type to lua somewhere (Probs engine.)
    type["texture"] = &TextureRect::texture;
}

void TextureRect::_on_create()
{
    SetDrawCall(drawCall);

    texture = node->engine->getResource<HeartModules::Texture>(textureName);
}

void TextureRect::_on_destroy()
{
    texture.reset();
}

void TextureRect::_on_draw()
{
    if (texture == nullptr)
        return;

    auto position = transform->getWorldPosition();
    auto scale = transform->getWorldScale();
    auto rotation = transform->getWorldRotation();

    DrawTexturePro(texture->texture,
    {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
    {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
    {0, 0},
    RAD2DEG * rotation.angle,        // RAD2DEG * rotation.angle,
    WHITE);
}

void TextureRect::set_texture(std::string p_textureName)
{
    textureName = p_textureName;
    texture = node->engine->getResource<HeartModules::Texture>(textureName);
}
}