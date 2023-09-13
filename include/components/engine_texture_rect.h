#include "node.h"

#include "engine.h"

#include "resources/engine_texture.h"

class EngineTextureRect : public Component
{
private:
    std::string textureName;
public:
    std::shared_ptr<EngineTexture> texture;

    EngineTextureRect(std::string name, std::string p_texture)
        : Component(name), textureName(p_texture) {}
    EngineTextureRect(std::string name) : Component(name) {}

    void _on_create() override
    {
        node->engine->drawEvent.append([this](){_on_draw(); });

        texture = node->engine->getResource<EngineTexture>(textureName);
    }

    void _on_destroy() override
    {
        texture.reset();
    }

    void _on_draw()
    {
        // auto position = getWorldPosition();

        DrawTexturePro(texture->texture,
        {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
        {200, 200, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
        {0, 0},
        0,
        WHITE);
    }

    void set_texture(std::string p_textureName)
    {
        textureName = p_textureName;
        texture = node->engine->getResource<EngineTexture>(textureName);
    }
};