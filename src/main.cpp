#include <map>
#include <memory>

#include "engine.h"

#include "components/engine_texture_rect.h"
#include "components/game_transform.h"

// #include "lua_wrappers/lua_wrapper.h"

class CustomTexture : public Component
{
private:
    EngineTextureRect* textureRect;
    GameTransform* transform;
public:
    CustomTexture(std::string name)
        : Component(name) {  }
    
    float spin = 0.0f;

    void _on_create() override
    {
        transform = node->getComponentT<GameTransform>("Transform");
        textureRect = node->getComponentT<EngineTextureRect>("TextureRect");

        node->engine->updateEvent.append([this](){ _update(); });

        transform->SetLocalPosition({200, 200, 0});
    }

    void _update()
    {
        spin += 200.0f * GetFrameTime();

        transform->SetLocalRotation({{0, 0, 1}, DEG2RAD * spin});
    }
};

int main()
{
    Engine engine = Engine();

    engine.loadResource(EngineTexture("Texture", ASSETS_PATH"test.png"));

    auto textureRect = engine.addNode(Node("TextureRect"));
    textureRect->addComponent(EngineTextureRect("TextureRect", "Texture"));
    auto textureRect1Transform = textureRect->addComponent(GameTransform("Transform", {200, 200, 0}, {{0, 0, 0}, 0}, {1, 1, 1}));
    textureRect->addComponent(CustomTexture("CustomTexture"));

    auto textureRect2 = engine.addNode(Node("TextureRect2"));
    textureRect2->addComponent(CustomTexture("CustomTexture"));
    textureRect2->addComponent(EngineTextureRect("TextureRect", "Texture"));
    textureRect2->addComponent(GameTransform("Transform", {250, 250, 0}, {{0, 0, 0}, 0}, {1, 1, 1}));
    textureRect2->getComponentT<GameTransform>("Transform")
        ->SetParent(textureRect1Transform);

    // auto ptr = std::dynamic_pointer_cast<CustomTexture>(textureRect2.lock());
    // ptr->setTexture("Texture");

    // textureRect2.lock()->setLocalPosition({200, 20, 20});

    // auto luaTest = engine.addNode(Node("LuaTest"));

    // LuaNode customTextureScript = LuaNode(textureRect2.lock());

    // std::string script = R"(
    //     print("Working!")
    //     val = getNode("/root")
    //     print(val.name)
    //     val:setName("pop")
    //     print(val.name)

    //     newNode = addNode("Node", "LuaTestNode", "")

    //     print(newNode.name)

    //     function _ready()
    //         print("Ready!")
    //     end
    // )";

    // customTextureScript.lua.set_function(
    //     "addNode",
    //     [&engine](std::string registeredType, std::string name, std::string parentPath = "") -> shared_node_ptr
    //     {
    //         auto newNode = engine.addNode(registeredType, name, parentPath);

    //         if (auto newNode_ptr = newNode.lock())
    //         {
    //             auto luaNode = std::make_unique<LuaNode>(LuaNode(newNode_ptr));

    //             wrappers[registeredType](luaNode->lua, *newNode_ptr.get());

    //             luaNode->init("");

    //             return newNode_ptr;
    //         }

    //         return nullptr;
    //     }
    // );

    // customTextureScript.init(script);

    engine.run();
    
    return 0;
}
