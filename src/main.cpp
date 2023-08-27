#include "engine.cpp"

//TODO: Add child relative to parent transform stuff.

class CustomTexture : public EngineTextureRect
{
public:
    CustomTexture(const char* name, std::shared_ptr<EngineTexture> texture) : EngineTextureRect(name, texture) {}

    void _ready()
    {
        Engine::ParentNode(this, "Game");
    }
};

int main()
{
    auto texture = std::make_shared<EngineTexture>(EngineTexture("Texture", ASSETS_PATH"test.png"));
    Engine::create()
        .addNode(Node("Game"))
        .loadResource(texture)
        .addNode(CustomTexture("TextureRect", texture))
        .run();
    return 0;
}
