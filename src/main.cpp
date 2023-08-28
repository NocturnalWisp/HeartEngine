#include "engine.cpp"

//TODO: Add child relative to parent transform stuff.

class CustomTexture : public EngineTextureRect
{
public:
    CustomTexture(const char* name, std::shared_ptr<EngineTexture> texture) : EngineTextureRect(name, texture) {}

    float spin = 0.0f;

    void _ready() override
    {
        EngineTextureRect::_ready();
        getNode("/root/Game").lock()->addChild(self);

        getNode("../").lock()->setLocalPosition({200, 200, 0});
    }

    void _update() override
    {
        EngineTextureRect::_update();

        // getNode("../").lock()->setLocalPosition(Vector3Scale(Vector3Add(parent.lock()->getLocalPosition(), {1, 1, 0}), 1));
        // getNode("../").lock()->setLocalRotation({{0, 0, 0}, parent.lock()->getLocalRotation().angle + 1});
        Debug::print(QuaternionToEuler(rotation).z);
        // Debug::print(Vector3Add(QuaternionToEuler(rotation), {0, 0, 0.000000001}).z);
        // auto newRotation = Vector3Add(QuaternionToEuler(rotation), Vector3Scale({0, 0, 10}, GetFrameTime()));
        // rotation = QuaternionFromEuler(newRotation.x, newRotation.y, newRotation.z);
        parent.lock()->setLocalRotation({{0, 0, 1}, spin});
        setLocalRotation({{0, 0, 1}, spin});

        spin += 1.0f;
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
