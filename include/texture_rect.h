#include "heart/node.h"

#include "heart/engine.h"

#include "heart/resources/texture.h"
#include "module/transform_3d.h"

namespace HeartEngine
{
class TextureRect : public Component
{
private:
    std::string textureName;
protected:
    HeartModules::Transform3D* transform;
public:
    std::shared_ptr<Texture> texture = nullptr;

    TextureRect(std::string name, std::string p_texture)
        : Component(name), textureName(p_texture) {}
    TextureRect(std::string name) : Component(name) {}
    TextureRect(std::string name, sol::variadic_args va) : Component(name)
    {
        if (va.size() > 0)
            textureName = va[0];
    }

    void populateLuaData() override
    {
        auto type = CREATEUSERTYPE(TextureRect);

        //TODO: Introduce texture type to lua somewhere (Probs engine.)
        type["texture"] = &TextureRect::texture;
    }

    void _on_create() override
    {
        node->engine->events["draw"].addListener([this](){_on_draw(); });

        texture = node->engine->getResource<Texture>(textureName);

        //TODO: Add component requirements (Allow referencing other components during constructor setup.)
        transform = &node->getComponentT<HeartModules::Transform3D>("Transform");
    }

    void _on_destroy() override
    {
        texture.reset();
    }

    void _on_draw()
    {
        if (texture == nullptr)
            return;

        auto position = transform->GetWorldPosition();
        auto scale = transform->GetWorldScale();
        auto rotation = transform->GetWorldRotation();

        DrawTexturePro(texture->texture,
        {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
        {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
        {0, 0},
        RAD2DEG * rotation.angle,        // RAD2DEG * rotation.angle,
        WHITE);
    }

    void set_texture(std::string p_textureName)
    {
        textureName = p_textureName;
        texture = node->engine->getResource<Texture>(textureName);
    }
};
}