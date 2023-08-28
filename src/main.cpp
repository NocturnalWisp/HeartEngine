#include "engine.cpp"

//TODO: Fix resources not deallocating because of classes?

class CustomTexture : public EngineTextureRect
{
public:
    CustomTexture(const char* name, const char* textureRes)
        : EngineTextureRect(name, textureRes) {}

    float spin = 0.0f;

    void _ready() override
    {
        EngineTextureRect::_ready();

        getNode("../").lock()->setLocalPosition({200, 200, 0});

        destroy();
    }

    void _update() override
    {
        EngineTextureRect::_update();

        // getNode("../").lock()->setLocalPosition(Vector3Scale(Vector3Add(parent.lock()->getLocalPosition(), {1, 1, 0}), 1));
        // getNode("../").lock()->setLocalRotation({{0, 0, 0}, parent.lock()->getLocalRotation().angle + 1});
        // Debug::print(Vector3Add(QuaternionToEuler(rotation), {0, 0, 0.000000001}).z);
        // auto newRotation = Vector3Add(QuaternionToEuler(rotation), Vector3Scale({0, 0, 10}, GetFrameTime()));
        // rotation = QuaternionFromEuler(newRotation.x, newRotation.y, newRotation.z);

        // Debug::print(QuaternionToEuler(rotation).z);
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
        .run();
    return 0;
}
