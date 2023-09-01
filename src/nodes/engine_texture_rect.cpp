#include "../include/node.h"

#include "../resources/engine_texture.cpp"

class EngineTextureRect : public Node
{
public:
    EngineTextureRect(const char* name, const char* p_texture)
        : Node(name), textureName(p_texture)
    {

    }
    EngineTextureRect(const char* name) : Node(name) {}

    const char* textureName;
    std::shared_ptr<EngineTexture> texture;

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
};