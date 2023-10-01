
#include "heart/engine.h"

#include "module/texture_rect.h"

#include "heart/module.h"

#include "module/raylib_core.h"
#include "module/raylib_input.h"
#include "module/raymath.h"
#include "module/transforms.h"
#include "module/resources/texture.h"
#include "module/drawables.h"

using namespace HeartEngine;
using namespace HeartModules;

class TestModule : public Module
{
public:
    void registerTypes(Engine& engine, sol::state& lua)
    {
    }
};

int main()
{
    Engine engine = Engine();

    engine.registerModule(HeartModules::RayLibCore());
    engine.registerModule(HeartModules::RayLibInput());
    engine.registerModule(HeartModules::RayMath(true, true, false, true));
    engine.registerModule(HeartModules::Transforms());
    engine.registerModule(HeartModules::Drawables());
    engine.registerModule(TestModule());

    engine.loadResource(HeartModules::Texture("Texture", "test.png"));

    auto luaTest = engine.addNode(Node("LuaTest"), "test.lua");

    engine.run();
    
    return 0;
}