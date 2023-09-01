#include "engine.h"

#include "nodes/engine_texture_rect.cpp"

class CustomTexture : public EngineTextureRect
{
public:
    CustomTexture(const char* name, const char* textureRes)
        : EngineTextureRect(name, textureRes) {  }

    float spin = 0.0f;

    void _ready() override
    {
        EngineTextureRect::_ready();

        getNode("../").lock()->setLocalPosition({200, 200, 0});
    }

    void _update() override
    {
        EngineTextureRect::_update();

        parent.lock()->setLocalRotation({{0, 0, 1}, spin});
        setLocalRotation({{0, 0, 1}, spin});

        spin += 1.0f;
    }
};

int main()
{
    Engine::create()
        .addNode(Node("Game"))
        .loadResource(EngineTexture("Texture", ASSETS_PATH"test.png"))
        .addNode(CustomTexture("TextureRect", "Texture"), "/root/Game")
        .addNode(CustomTexture("TextureRect2", "Texture"), "/root/Game")
        .inlineDoSomething([](){ Engine::getRoot().lock()->getNode("Game/TextureRect2").lock()->setLocalPosition({200, 20, 20}); })
        .run();
    
    return 0;
}
