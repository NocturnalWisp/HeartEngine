#include <map>
#include <memory>

#include "engine.h"

#include "nodes/engine_texture_rect.h"

#include "lua_wrappers/lua_wrapper.h"

class CustomTexture : public EngineTextureRect
{
public:
    CustomTexture(std::string name, std::string textureRes)
        : EngineTextureRect(name, textureRes) {  }

    CustomTexture(std::string name)
        : EngineTextureRect(name) {  }

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
    Engine engine = Engine();

    engine.addNode(Node("Game"));

    engine.registerNodeType("Node", [](std::string name) -> shared_node_ptr { return std::make_shared<Node>(name); });
    engine.registerNodeType("CustomTexture", [](std::string name) -> shared_node_ptr { return std::make_shared<CustomTexture>(name); });

    engine.loadResource(EngineTexture("Texture", ASSETS_PATH"test.png"));

    engine.addNode(CustomTexture("TextureRect", "Texture"), "/root");
    auto textureRect2 = engine.addNode("CustomTexture", "TextureRect2", "/root");
    // engine.addNode(CustomTexture("TextureRect2", "Texture"), "/root");

    auto ptr = std::dynamic_pointer_cast<CustomTexture>(textureRect2.lock());
    ptr->setTexture("Texture");

    textureRect2.lock()->setLocalPosition({200, 20, 20});

    auto luaTest = engine.addNode(Node("LuaTest"));

    LuaNode customTextureScript = LuaNode(textureRect2.lock());

    std::string script = R"(
        print("Working!")
        val = getNode("/root")
        print(val.name)
        val:setName("pop")
        print(val.name)

        newNode = addNode("Node", "LuaTestNode", "")

        print(newNode.name)

        function _ready()
            print("Ready!")
        end
    )";

    customTextureScript.lua.set_function(
        "addNode",
        [&engine](std::string registeredType, std::string name, std::string parentPath = "") -> shared_node_ptr
        {
            auto newNode = engine.addNode(registeredType, name, parentPath);

            if (auto newNode_ptr = newNode.lock())
            {
                auto luaNode = std::make_unique<LuaNode>(LuaNode(newNode_ptr));

                wrappers[registeredType](luaNode->lua, *newNode_ptr.get());

                luaNode->init("");

                return newNode_ptr;
            }

            return nullptr;
        }
    );

    customTextureScript.init(script);

    engine.run();
    
    return 0;
}
