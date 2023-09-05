#include "engine.h"

#include "nodes/engine_texture_rect.cpp"

#include "lua_wrappers/lw_node.cpp"

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
    Engine engine = Engine();

    engine.addNode(Node("Game"));
    engine.loadResource(EngineTexture("Texture", ASSETS_PATH"test.png"));
    engine.addNode(CustomTexture("TextureRect", "Texture"), "/root");
    auto textureRect2 = engine.addNode(CustomTexture("TextureRect2", "Texture"), "/root");

    textureRect2.lock()->setLocalPosition({200, 20, 20});

    auto luaTest = engine.addNode(Node("LuaTest"));

    {
        sol::state lua;
        lua.open_libraries(sol::lib::base);

        lw_getNodeWrapper(lua, *luaTest.lock().get());

        lua.script(R"(
            print("Working!")
            val = getNode("/root")
            print(val.name)
            val:setName("pop")
            print(val.name)
        )");
    }

    engine.run();
    
    return 0;
}
