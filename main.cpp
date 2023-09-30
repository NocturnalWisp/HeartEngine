#include <map>
#include <memory>

#ifndef EDITOR
#define EDITOR
#endif

#include "heart/engine.h"

#include "texture_rect.h"

#include "heart/file_manager.h"

#include "heart/module.h"

#include "module/raylib_core.h"
#include "module/raymath.h"
#include "module/transforms.h"
#include "module/transform_3d.h"

using namespace HeartEngine;
using namespace HeartModules;

class TestModule : public Module
{
public:
    void registerTypes(Engine& engine, sol::state& lua)
    {
        engine.registerComponent("TextureRect", &Engine::componentBuilder<TextureRect>);
    }
};

int main()
{
    Engine engine = Engine();

    engine.registerModule(HeartModules::RayLibCore());
    engine.registerModule(HeartModules::Transforms());
    engine.registerModule(HeartModules::RayMath(true, true, false, true));
    engine.registerModule(TestModule());

    engine.loadResource(HeartEngine::Texture("Texture", "test.png"));

    auto luaTest = engine.addNode(Node("LuaTest"), "test.lua");

    engine.run();
    
    return 0;
}