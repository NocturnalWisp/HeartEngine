#include <map>
#include <memory>

#include "engine.h"

#include "components/engine_texture_rect.h"
#include "components/game_transform.h"

#include "lua_wrappers/lua_node.h"

class CustomTexture : public Component
{
private:
    EngineTextureRect* textureRect;
    GameTransform* transform;
public:
    CustomTexture(std::string name)
        : Component(name) {  }
    
    float spin = 0.0f;

    EventHandle* handle;

    void _on_create() override
    {
        transform = node->getComponentT<GameTransform>("Transform");
        textureRect = node->getComponentT<EngineTextureRect>("TextureRect");

        node->engine->updateEvent.append([this](){ _update(); });

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

template <class T>
std::unique_ptr<Component> registerComponentType(std::string name)
{
    static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component.");
    return std::make_unique<T>(T(name));
}

int main()
{
    Debug::print("Yeah");
    Engine engine = Engine();

    engine.registerComponent("Transform", &registerComponentType<GameTransform>);
    engine.registerComponent("EngineTextureRect", &registerComponentType<EngineTextureRect>);

    engine.loadResource(EngineTexture("Texture", "assets/test.png"));

    auto textureRect = engine.addNode(Node("TextureRect"));
    textureRect->addComponent(EngineTextureRect("TextureRect", "Texture"));
    auto textureRect1Transform = textureRect->addComponent(GameTransform("Transform", {200, 200, 0}, {{0, 0, 0}, 0}, {1, 1, 1}));
    // textureRect->addComponent(CustomTexture("CustomTexture"));

    auto textureRect2 = engine.addNode(Node("TextureRect2"));
    textureRect2->addComponent(CustomTexture("CustomTexture"));
    textureRect2->addComponent(EngineTextureRect("TextureRect", "Texture"));
    textureRect2->addComponent(GameTransform("Transform", {250, 250, 0}, {{0, 0, 0}, 0}, {1, 1, 1}));

    textureRect2->getComponentT<GameTransform>("Transform")
        ->SetParent(textureRect1Transform);

    auto luaTest = engine.addNode<LuaNode>(LuaNode("LuaTest"));

    luaTest->lua.new_usertype<Vector3>("Vector3",
        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z
    );

    luaTest->init("assets/test.lua");

    Debug::print(luaTest->getComponentT<GameTransform>("c_transform")
        ->GetLocalPosition().x);

    engine.run();
    
    return 0;
}
