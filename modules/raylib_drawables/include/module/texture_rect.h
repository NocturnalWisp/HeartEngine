#pragma once

#include "heart/node.h"

#include "heart/engine.h"

#include "module/resources/texture.h"
#include "module/transform_3d.h"

namespace HeartModules
{
class TextureRect : public Component
{
    REQUIRE_COMPONENTS(transform)

    DRAW_CALLABLE(_on_draw())
private:
    std::string textureName;
protected:
    HeartModules::Transform3D* transform;
public:
    std::shared_ptr<HeartModules::Texture> texture = nullptr;

    TextureRect(std::string p_name, std::string p_textureName)
        : Component(p_name), textureName(p_textureName) {}
    TextureRect(std::string name, sol::variadic_args va);

    void populateLuaData() override;

    void _on_create() override;

    void _on_destroy() override;

    void _on_draw();

    void set_texture(std::string p_textureName);
};
}