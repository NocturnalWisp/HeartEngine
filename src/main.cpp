#include "engine.cpp"

//TODO: Add child relative to parent transform stuff.

class CustomTexture : public EngineTextureRect
{
public:
    CustomTexture(const char* name, std::shared_ptr<EngineTexture> texture) : EngineTextureRect(name, texture) {}

    void _ready() override
    {
        EngineTextureRect::_ready();
        getNode("/root/Game").addChild(self);
    }
};

int main()
{
    auto texture = std::make_shared<EngineTexture>(EngineTexture("Texture", ASSETS_PATH"test.png"));
    Engine::create()
        .addNodeRoot(Node("Game"))
        .loadResource(texture)
        .addNodeRoot(CustomTexture("TextureRect", texture))
        .run();
    return 0;
}
