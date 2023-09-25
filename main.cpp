#include <map>
#include <memory>

#include "engine.h"

#include "components/texture_rect.h"
#include "components/transform.h"

#include "file_manager.h"

namespace HeartEngine
{
class CustomTexture : public Component
{
private:
    TextureRect* textureRect;
    Transform3D* transform;
public:
    CustomTexture(std::string name)
        : Component(name) {  }
    CustomTexture(std::string name, sol::variadic_args va) : Component(name) {}
    
    float spin = 0.0f;

    EventHandle* handle;

    void populateLuaData() override
    {
        auto type = CREATEUSERTYPE(CustomTexture);

        type["spin"] = &CustomTexture::spin;
    }

    void _on_create() override
    {
        transform = node->getComponentT<Transform3D>("Transform");
        textureRect = node->getComponentT<TextureRect>("TextureRect");

        node->engine->updateEvent.addListener([this](){ _update(); });

        transform->SetLocalPosition({200, 200, 0});

        std::function<void()> function = std::bind(&test, this);
        handle = node->addEventListener("test", function);
    }

    void test()
    {
        Debug::print("blegh");
    }

    void _update()
    {
        spin += 200.0f * GetFrameTime();

        transform->SetLocalRotation({{0, 0, 1}, DEG2RAD * spin});
    }
};
}

int main()
{
    using namespace HeartEngine;

    Engine engine = Engine();

    engine.registerComponent("Transform", &Engine::registerComponentType<Transform3D>);
    engine.registerComponent("TextureRect", &Engine::registerComponentType<TextureRect>);
    engine.registerComponent("CustomTexture", &Engine::registerComponentType<CustomTexture>);

    engine.loadResource(HeartEngine::Texture("Texture", "test.png"));

    auto luaTest = engine.addNode(Node("LuaTest"), "test.lua");

    engine.run();
    
    return 0;
}