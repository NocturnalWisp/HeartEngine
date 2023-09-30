#include <map>
#include <memory>

#ifndef EDITOR
#define EDITOR
#endif

#include "heart/engine.h"

#include "texture_rect.h"
#include "module/transforms.h"
#include "module/transform_3d.h"

#include "heart/file_manager.h"

#include "heart/module.h"
#include "module/raymath.h"

using namespace HeartEngine;
using namespace HeartModules;

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
        transform = &node->getComponentT<Transform3D>("Transform");
        textureRect = &node->getComponentT<TextureRect>("TextureRect");


        node->engine->events["update"].addListener([this](){ _update(); });

        transform->SetLocalPosition({200, 200, 0});

        std::function<void()> function = std::bind(&test, this);
        handle = node->events["test"].addListener(function);
    }

    void test()
    {
        Debug::PRINT("blegh", 2);
    }

    void _update()
    {
        spin += 200.0f * GetFrameTime();

        transform->SetLocalRotation({{0, 0, 1}, DEG2RAD * spin});
    }
};

class TestModule : public Module
{
public:
    void registerTypes(Engine& engine, sol::state& lua)
    {
        engine.registerComponent("TextureRect", &Engine::componentBuilder<TextureRect>);
        engine.registerComponent("CustomTexture", &Engine::componentBuilder<CustomTexture>);
    }
};

int main()
{
    Engine engine = Engine();

    engine.registerModule(HeartModules::Transforms());
    engine.registerModule(HeartModules::RayMath());
    engine.registerModule(TestModule());

    engine.loadResource(HeartEngine::Texture("Texture", "test.png"));

    auto luaTest = engine.addNode(Node("LuaTest"), "test.lua");

    engine.run();
    
    return 0;
}