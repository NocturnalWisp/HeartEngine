#pragma once

#include <optional>

#include "heart/utils.h"
#include "heart/engine.h"

#include "module/resources/texture.h"

namespace HeartRayLib
{
class TextureRect : public Component
{
    EVENT_CALLABLE(draw, _on_draw());
private:
    std::string textureName;
public:
    std::shared_ptr<HeartRayLib::Texture> texture = nullptr;
    std::optional<Rectangle> source;
    Rectangle rect;
    float rotation;
    // Percentage 0-1
    raylib::Vector2 origin;
    Color color;

    TextureRect(std::string p_name,
        std::string p_textureName = "",
        std::optional<Rectangle> source = std::nullopt,
        Rectangle rect = {0, 0, 10, 10},
        float rotation = 0,
        raylib::Vector2 origin = Vector2Zero(),
        Color color = WHITE)
        : Component(p_name),
          textureName(p_textureName),
          source(source),
          rect(rect),
          rotation(rotation),
          origin(origin),
          color(color) {}
    TextureRect(std::string name, sol::variadic_args va);

    void populateLuaData() override;

    void _on_create() override;

    void _on_destroy() override;

    void _on_draw();

    void set_texture(std::string p_textureName);
};
}