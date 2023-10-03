#pragma once

#include "heart/node.h"

#include "heart/engine.h"

#include "module/resources/texture.h"
#include "module/transform_3d.h"

namespace HeartModules
{
class TextureRect : public Component
{
private:
    std::string textureName;
protected:
    HeartModules::Transform3D* transform;
public:
    std::shared_ptr<HeartModules::Texture> texture = nullptr;

    TextureRect(std::string name, std::string p_texture)
        : Component(name), textureName(p_texture) {}
    TextureRect(std::string name) : Component(name) {}
    TextureRect(std::string name, sol::variadic_args va) : Component(name)
    {
        if (va.size() > 0)
            textureName = va[0];
    }

    void populateLuaData() override;

    void _on_create() override;

    void _on_destroy() override;

    void _on_draw();

    void set_texture(std::string p_textureName);
};
}