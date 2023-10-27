#pragma once

#include <optional>

#include "heart/utils.h"
#include "heart/engine.h"

#include "module/resources/texture.h"

#include "module/utils.h"

namespace HeartRayLib
{
class TextureRect : public Component
{
    EVENT_CALLABLE(draw, _on_draw());
private:
    std::string textureName;
public:
    std::shared_ptr<HeartRayLib::Texture> texture = nullptr;
    raylib::Rectangle source;
    raylib::Rectangle rect;
    float rotation;
    // Percentage 0-1
    raylib::Vector2 origin;
    Color color;

    TextureRect(std::string p_name,
        std::string p_textureName = "",
        raylib::Rectangle rect = {0, 0, 10, 10},
        float rotation = 0,
        raylib::Vector2 origin = Vector2Zero(),
        Color color = WHITE)
        : Component(p_name),
          textureName(p_textureName),
          rect(rect),
          rotation(rotation),
          origin(origin),
          color(color) {}
    TextureRect(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Texture Name
        CHECK_ARG(0, std::string, textureName = *result);
        // Rect
        CHECK_ARG(1, raylib::Rectangle, rect = *result);
        CHECK_ARG(1, std::vector<float>, rect = tableToRectangle(*result));
        // Rotation
        CHECK_ARG(2, float, rotation = *result);
        // Origin
        CHECK_ARG(3, Vector2, origin = *result);
        CHECK_ARG(3, std::vector<float>, origin = tableToVector2(*result));

        // Color
        CHECK_ARG(4, Color, color = *result);
        // Color as int (hex)
        CHECK_ARG(4, int, color = GetColor(*result));
        // Color as vector of floats (rgba)
        CHECK_ARG(4, std::vector<float>, color = tableToColor(*result));
    }

    void populateLuaData() override
    {
        auto type = CREATE_USER_TYPE(TextureRect);

        ADD_LUA_FUNCTION_W_TYPE(type, TextureRect, texture);
        ADD_LUA_FUNCTION_W_TYPE(type, TextureRect, rect);
        ADD_LUA_FUNCTION_W_TYPE(type, TextureRect, rotation);
        ADD_LUA_FUNCTION_W_TYPE(type, TextureRect, origin);
        ADD_LUA_FUNCTION_W_TYPE(type, TextureRect, color);
    }

    void _on_create() override
    {
        setdrawCall(drawCall);

        texture = node->engine->getResource<HeartRayLib::Texture>(textureName);
    }

    void _on_destroy() override
    {
        texture.reset();
    }

    void _on_draw()
    {
        // Origin is percentile based: 0 = start, 1 = end.
        auto actualOrigin = Vector2Multiply(origin, rect.GetSize());
        if (texture != nullptr)
        {
            auto textureSize = raylib::Vector2(texture->texture.width, texture->texture.height);

            auto actualScale = Vector2Multiply(rect.GetSize(), textureSize);

            DrawTexturePro(texture->texture,
                source,
                rect,
                origin,
                rotation,
                color
            );
        }
        else
        {
            DrawRectanglePro(
                rect,
                origin,
                rotation,
                color);
        }
    }

    void set_texture(std::string p_textureName)
    {
        textureName = p_textureName;
        texture = node->engine->getResource<HeartRayLib::Texture>(textureName);

        // Setup source to look over whole texture.
        source.x = 0;
        source.y = 0;
        source.width = texture->texture.width;
        source.height = texture->texture.height;
    }
};
}