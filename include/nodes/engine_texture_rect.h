#include "node.h"

#include "engine.h"

#include "resources/engine_texture.h"

class EngineTextureRect : public Node
{
public:
    EngineTextureRect(std::string name, std::string p_texture)
        : Node(name), textureName(p_texture)
    {

    }
    EngineTextureRect(std::string name) : Node(name) {}

    void _ready() override
    {
        texture = Engine::getResource<EngineTexture>(textureName);
    }

    void _draw() override
    {
        auto position = getWorldPosition();

        DrawTexturePro(texture->texture,
        {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
        {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
        {0, 0},
        QuaternionToEuler(rotation).z,
        modulate);
    }

    void _remove() override
    {
        texture.reset();
    }

    void setTexture(std::string p_textureName)
    {
        textureName = p_textureName;
        texture = Engine::getResource<EngineTexture>(textureName);
    }
private:
    std::string textureName;
    std::shared_ptr<EngineTexture> texture;
};